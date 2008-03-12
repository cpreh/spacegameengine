/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <iterator>
#include <algorithm>
#include <functional>
#include <boost/cast.hpp>
#include "../../../bit.hpp"
#include "../../../exception.hpp"
#include "../../../raw_vector.hpp"
#include "../../../util.hpp"
#include "../../../renderer/transform.hpp"
#include "../enumeration.hpp"
#include "../renderer.hpp"
#include "../texture.hpp"
#include "../volume_texture.hpp"
#include "../cube_texture.hpp"
#include "../vertex_buffer.hpp"
#include "../index_buffer.hpp"
#include "../constants.hpp"
#include "../conversion.hpp"
#include "../resource.hpp"
#include "../render_target.hpp"
#include "../../../stub.hpp"

namespace
{

void set_render_state(sge::d3d9::d3d_device_ptr device, D3DRENDERSTATETYPE state, sge::renderer::bool_type value);
void set_render_state(sge::d3d9::d3d_device_ptr Device, D3DRENDERSTATETYPE state, sge::renderer::int_type value);
void set_render_state(sge::d3d9::d3d_device_ptr device, D3DRENDERSTATETYPE state, sge::renderer::float_type value);
void set_sampler_state(sge::d3d9::d3d_device_ptr device, sge::stage_type stage, D3DSAMPLERSTATETYPE state, sge::renderer::int_type value);
void set_texture(sge::d3d9::d3d_device_ptr device, sge::stage_type stage, IDirect3DBaseTexture9* tex);
void set_texture_stage_state(sge::d3d9::d3d_device_ptr device, sge::stage_type stage, D3DTEXTURESTAGESTATETYPE state, sge::renderer::int_type value);
void set_transform(sge::d3d9::d3d_device_ptr device, D3DTRANSFORMSTATETYPE, const sge::math::space_matrix&);

}

sge::d3d9::renderer::renderer(
	const d3d_device_ptr device,
	const renderer_parameters& param,
	const adapter_type adapter,
  const win32_window_ptr wnd,
  const d3d_ptr sys)
: sys(sys),
  device(device),
  adapter(adapter),
  parameters(param),
  render_window(wnd),
	caps_(create_renderer_caps(adapter, sys))
{
	init();
}

void sge::d3d9::renderer::init()
{
	IDirect3DSurface9* surface;
	if(device->GetRenderTarget(0,&surface) != D3D_OK)
		throw exception(SGE_TEXT("d3d: cannot obtain default render target!"));
	default_render_target.reset(surface);
	std::for_each(resources.begin(),resources.end(),std::mem_fun(&resource::on_reset));
}

void sge::d3d9::renderer::release_resources()
{
	std::for_each(resources.begin(),resources.end(),std::mem_fun(&resource::on_loss));
	default_render_target.reset();
	vertex_declaration.reset();
}

const sge::vertex_buffer_ptr
sge::d3d9::renderer::create_vertex_buffer(
	const sge::vertex_format& format,
	const vertex_buffer::size_type size,
	const resource_flag_t flags,
	const vertex_buffer::const_pointer data)
{
	return vertex_buffer_ptr(
		new vertex_buffer(
			*this,
			device,
			format,
			size,
			flags,
			data));
}

const sge::index_buffer_ptr
sge::d3d9::renderer::create_index_buffer(
	const index_buffer::size_type size,
	const resource_flag_t flags,
	const index_buffer::const_pointer data)
{
	return index_buffer_ptr(
		new index_buffer(
			*this,
			device,
			size,
			flags,
			data));
}

const sge::texture_ptr
sge::d3d9::renderer::create_texture(
	const texture::const_pointer data,
	const texture::dim_type& dim,
	const filter_args& filter,
	const resource_flag_t flags)
{
	return texture_ptr(
		new texture(
			*this,
			device,
			data,
			dim,
			filter,
			flags));
}

const sge::volume_texture_ptr
sge::d3d9::renderer::create_volume_texture(
	const volume_texture::const_pointer data,
	const volume_texture::box_type& box,
	const filter_args& filter,
	const resource_flag_t flags)
{
	return volume_texture_ptr(
		new volume_texture(
			*this,
			device,
			data,
			box,
			filter,
			flags));
}

const sge::cube_texture_ptr
sge::d3d9::renderer::create_cube_texture(
	const cube_side_array* const src,
	const cube_texture::size_type size,
	const filter_args& filter,
	const resource_flag_t flags)
{
	return cube_texture_ptr(
		new cube_texture(
			*this,
			device,
			src,
			size,
			filter,
			flags));
}

const sge::render_target_ptr sge::d3d9::renderer::create_render_target(
	const render_target::dim_type& dim)
{
	return render_target_ptr(
		new render_target(
			*this,
			device,
			dim));
}

const sge::window_ptr
sge::d3d9::renderer::get_window() const
{
	return render_window;
}

void sge::d3d9::renderer::set_vertex_buffer(const vertex_buffer_ptr buffer)
{
	if(!buffer)
		return; //FIXME

	d3d9::vertex_buffer& d3d_buffer = dynamic_cast<d3d9::vertex_buffer&>(*buffer);
	const d3d_vertex_declaration_ptr decl = d3d_buffer.d3d_format.vertex_declaration();
	if(decl != vertex_declaration)
	{
		if(device->SetVertexDeclaration(decl.get()) != D3D_OK)
			throw exception(SGE_TEXT("set_vertex_declaration() failed"));
		vertex_declaration = decl;
	}
	if(device->SetStreamSource(0,d3d_buffer.buffer.get(),0,static_cast<UINT>(buffer->stride())) != D3D_OK)
		throw exception(SGE_TEXT("set_vertex_buffer() failed"));
}

void sge::d3d9::renderer::set_index_buffer(const index_buffer_ptr buffer)
{
	if(!buffer)
		return; //FIXME

	d3d9::index_buffer* const d3d_buffer = boost::polymorphic_cast<d3d9::index_buffer*>(buffer.get());
	if(device->SetIndices(d3d_buffer->buffer.get()) != D3D_OK)
		throw exception(SGE_TEXT("set_index_buffer() failed"));
}

void sge::d3d9::renderer::set_render_target(const texture_ptr target)
{
	if(!target)
	{
		if(device->SetRenderTarget(0,default_render_target.get()) != D3D_OK)
			throw exception(SGE_TEXT("cannot set default render target!"));
		return;
	}

	render_target* const d3d_target = boost::polymorphic_cast<render_target*>(target.get());

	if(device->SetRenderTarget(0,d3d_target->surface.get()) != D3D_OK)
		throw exception(SGE_TEXT("cannot set texture as render target!"));
}

void sge::d3d9::renderer::set_material(const material& m)
{
	if(device->SetMaterial(reinterpret_cast<const D3DMATERIAL9*>(&m)) != D3D_OK)
		throw exception(SGE_TEXT("set_material() failed!"));
}

void sge::d3d9::renderer::reset(const renderer_parameters* const param)
{
	release_resources();

	if(param)
	{
		if(parameters.mode.width() != param->mode.width() ||
		   parameters.mode.height() != param->mode.height())
		{
			render_window->size(window::window_size(param->mode.width(), param->mode.height()));
			parameters.mode = param->mode;
		}
		parameters.samples = param->samples;
		parameters.windowed = param->windowed;
		parameters.vsync = param->vsync;
	}

	D3DPRESENT_PARAMETERS pp = create_present_parameters(parameters, adapter, render_window, sys);

	while(device->TestCooperativeLevel() == D3DERR_DEVICELOST)
		sge::sleep(1);

	const HRESULT reset_res = device->Reset(&pp);
	switch(reset_res) {
	case D3D_OK:
		init();
		break;
	case D3DERR_DEVICELOST:
		throw exception(SGE_TEXT("d3d device still lost!"));
	case D3DERR_DRIVERINTERNALERROR:
		throw exception(SGE_TEXT("d3d driver internal error!"));
	case D3DERR_INVALIDCALL:
		throw exception(SGE_TEXT("d3d invalid call to reset!"));
	default:
		throw exception(SGE_TEXT("d3d reset failed!"));
	}
}

void sge::d3d9::renderer::set_texture(const texture_base_ptr p, const stage_type stage)
{
	if(!p)
		return ::set_texture(device, stage, 0);

	texture_base* const tex_base = boost::polymorphic_cast<texture_base*>(p.get());
	::set_texture(device, stage, tex_base->base);
}

void sge::d3d9::renderer::set_texture_stage_op(const stage_type stage,
                                               const texture_stage_op::type type,
                                               const texture_stage_op_value::type value)
{
	const D3DTEXTURESTAGESTATETYPE d3d_type = convert_cast<D3DTEXTURESTAGESTATETYPE>(type);
	const DWORD d3d_value = convert_cast<DWORD>(value);
	set_texture_stage_state(device, stage, d3d_type, d3d_value);
}

void sge::d3d9::renderer::set_texture_stage_arg(const stage_type stage,
                                                const texture_stage_arg::type type,
                                                const texture_stage_arg_value::type value)
{
	const D3DTEXTURESTAGESTATETYPE d3d_type = convert_cast<D3DTEXTURESTAGESTATETYPE>(type);
	const DWORD d3d_value = convert_cast<DWORD>(value);
	set_texture_stage_state(device, stage, d3d_type, d3d_value);
}

/*void sge::d3d9::renderer::set_filter_state(const stage_type stage, const filter_arg type, const filter_arg_value value)
{
	const D3DSAMPLERSTATETYPE d3d_type = convert_cast<D3DSAMPLERSTATETYPE>(type);
	const D3DTEXTUREFILTERTYPE d3d_value = convert_cast<D3DTEXTUREFILTERTYPE>(value);
	set_sampler_state(device,stage,d3d_type,d3d_value);
}*/

void sge::d3d9::renderer::render(const vertex_buffer_ptr nvb,
                                 const index_buffer_ptr nib,
                                 const sge::vertex_buffer::size_type first_vertex,
                                 const sge::vertex_buffer::size_type num_vertices,
                                 const indexed_primitive_type::type ptype,
                                 const sge::index_buffer::size_type pcount,
                                 const sge::index_buffer::size_type first_index)
{
	const D3DPRIMITIVETYPE prim_type = convert_cast<D3DPRIMITIVETYPE>(ptype);
	if(vb != nvb)
		set_vertex_buffer(nvb);

	if(ib != nib)
		set_index_buffer(nib);
	if(device->DrawIndexedPrimitive(prim_type,
	                                0,
	                                static_cast<UINT>(first_vertex),
	                                static_cast<UINT>(num_vertices),
	                                static_cast<UINT>(first_index),
	                                static_cast<UINT>(pcount)
	)!= D3D_OK)
		throw exception(SGE_TEXT("DrawIndexedPrimitive() failed!"));
}

void sge::d3d9::renderer::render(const vertex_buffer_ptr nvb,
                                 const sge::vertex_buffer::size_type first_vertex,
                                 const sge::vertex_buffer::size_type num_vertices,
                                 const nonindexed_primitive_type::type ptype)
{
	const D3DPRIMITIVETYPE prim_type = convert_cast<D3DPRIMITIVETYPE>(ptype);
	if(vb != nvb)
		set_vertex_buffer(nvb);

	if(device->DrawPrimitive(prim_type,
	                         static_cast<UINT>(first_vertex),
	                         static_cast<UINT>(primitive_count(num_vertices, ptype))
	) != D3D_OK)
		throw exception(SGE_TEXT("DrawPrimitive() failed!"));
}

void sge::d3d9::renderer::begin_rendering()
{
//	if(device->Clear(0,0,clear_flags,clear_color,zbuffer_clear_val,stencil_clear_val) != D3D_OK)
//		throw exception(SGE_TEXT("Clear() failed!"));
	if(device->BeginScene() != D3D_OK)
		throw exception(SGE_TEXT("BeginScene() failed!"));
}

void sge::d3d9::renderer::end_rendering()
{
	if(device->EndScene() != D3D_OK)
		throw exception(SGE_TEXT("EndScene() failed!"));

	const HRESULT present_res = device->Present(0,0,0,0);
	switch(present_res) {
	case D3D_OK:
		break;
	case D3DERR_DEVICELOST:
		// TODO: Handle DEVICELOST
	default:
		throw exception(SGE_TEXT("Present() failed!"));
	}
}

void sge::d3d9::renderer::set_state(const renderer_state_list& list)
{
}

void sge::d3d9::renderer::push_state(const renderer_state_list& list)
{
}

void sge::d3d9::renderer::pop_level()
{
}

/*
void sge::d3d9::renderer::set_bool_state(const bool_state::type state, const bool_type value)
{
	switch(state) {
	case bool_state::clear_zbuffer:
		set_bit(D3DCLEAR_ZBUFFER, clear_flags, value);
		break;
	case bool_state::clear_stencil:
		set_bit(D3DCLEAR_STENCIL, clear_flags, value);
		break;
	case bool_state::clear_backbuffer:
		set_bit(D3DCLEAR_TARGET, clear_flags, value);
		break;
	case bool_state::enable_fog:
		set_render_state(device,D3DRS_FOGENABLE,value);
		break;
  case BS_EnableRangeFog:
		set_render_state(device,D3DRS_RANGEFOGENABLE,value);
		break;
	case bool_state::enable_stencil:
		set_render_state(device,D3DRS_STENCILENABLE,value);
		break;
	case bool_state::enable_alpha_blending:
		set_render_state(device,D3DRS_ALPHABLENDENABLE,value);
		if(value)
		{
			set_render_state(device,D3DRS_SRCBLEND, int_type(D3DBLEND_SRCALPHA) );
			set_render_state(device,D3DRS_DESTBLEND, int_type(D3DBLEND_INVSRCALPHA) );
		}
		else
		{
			set_render_state(device,D3DRS_SRCBLEND, int_type(D3DBLEND_ONE) );
			set_render_state(device,D3DRS_DESTBLEND, int_type(D3DBLEND_ZERO) );
		}
		break;
	case bool_state::enable_zbuffer:
		set_render_state(device,D3DRS_ZENABLE,value);
		break;
	}
}

void sge::d3d9::renderer::set_float_state(const float_state::type state, const float_type value)
{
	switch(state) {
	case float_state::zbuffer_clear_val:
		zbuffer_clear_val = value;
		break;
	case float_state::fog_start:
		set_render_state(device,D3DRS_FOGSTART,value);
		break;
	case float_state::fog_end:
		set_render_state(device,D3DRS_FOGEND,value);
		break;
	case float_state::fog_density:
		set_render_state(device,D3DRS_FOGDENSITY,value);
		break;
	}
}

void sge::d3d9::renderer::set_int_state(const int_state::type state, const int_type value)
{
	switch(state) {
	case IS_FogMode:
		set_render_state(device,D3DRS_FOGTABLEMODE,value);
		break;
	case int_state::stencil_clear_val:
		stencil_clear_val = value;
		break;
	}
}

void sge::d3d9::renderer::set_color_state(const color_state::type state, const color value)
{
	switch(state) {
	case color_state::ambient_light_color:
		set_render_state(device,D3DRS_AMBIENT,value);
		break;
	case color_state::fog_color:
		set_render_state(device,D3DRS_FOGCOLOR,value);
		break;
	case color_state::clear_color:
		clear_color = value;
		break;
	}
}

void sge::d3d9::renderer::set_cull_mode(const cull_mode::type mode)
{
	SGE_STUB_FUNCTION
}

void sge::d3d9::renderer::set_depth_func(const depth_func::type func)
{
	SGE_STUB_FUNCTION
}

void sge::d3d9::renderer::set_stencil_func(const stencil_func::type func,
                                           const signed_type value,
                                           const unsigned_type mask)
{
	SGE_STUB_FUNCTION
}

void sge::d3d9::renderer::set_fog_mode(const fog_mode::type mode)
{
	SGE_STUB_FUNCTION
}

void sge::d3d9::renderer::set_blend_func(const source_blend_func::type source,
                                         const dest_blend_func::type dest)
{
	SGE_STUB_FUNCTION
}

void sge::d3d9::renderer::set_draw_mode(const draw_mode::type mode)
{
	SGE_STUB_FUNCTION
}
*/

void sge::d3d9::renderer::set_viewport(const viewport& v)
{
	SGE_STUB_FUNCTION
}

void sge::d3d9::renderer::enable_light(const light_index index,
                                       const bool enable)
{
	SGE_STUB_FUNCTION
}

void sge::d3d9::renderer::set_light(const light_index index,
                                    const light& l)
{
	SGE_STUB_FUNCTION
}

const sge::glsl::program_ptr
sge::d3d9::renderer::create_glsl_program(
	const std::string&,
	const std::string&)
{
	return glsl::program_ptr();
}

void sge::d3d9::renderer::set_glsl_shader(const glsl::program_ptr)
{
	throw exception(SGE_TEXT("set_glsl_shader(): D3D9 does not support GLSL!"));
}

const sge::render_target_ptr sge::d3d9::renderer::get_render_target() const
{
	SGE_STUB_FUNCTION
	return render_target_ptr(); //default_render_target; // FIXME
}

void sge::d3d9::renderer::transform(const math::space_matrix& m)
{
	set_transform(device, D3DTS_WORLD, m);
}

void sge::d3d9::renderer::projection(const math::space_matrix& m)
{
	set_transform(device, D3DTS_PROJECTION, m);
}

const sge::renderer_caps& sge::d3d9::renderer::caps() const
{
	return caps_;
}

const sge::screen_size_t
sge::d3d9::renderer::screen_size() const
{
	return parameters.mode.size;
}

namespace
{

void set_render_state(const sge::d3d9::d3d_device_ptr device, const D3DRENDERSTATETYPE state, const sge::renderer::bool_type value)
{
	if(device->SetRenderState(state,value) != D3D_OK)
		throw sge::exception(SGE_TEXT("SetRenderState() failed!"));
}

void set_render_state(const sge::d3d9::d3d_device_ptr device, const D3DRENDERSTATETYPE state, const sge::renderer::int_type value)
{
	if(device->SetRenderState(state,value) != D3D_OK)
		throw sge::exception(SGE_TEXT("SetRenderState() failed!"));
}

void set_render_state(const sge::d3d9::d3d_device_ptr device, const D3DRENDERSTATETYPE state, const sge::renderer::float_type value)
{
	if(device->SetRenderState(state,reinterpret_cast<const DWORD&>(value)) != D3D_OK)
		throw sge::exception(SGE_TEXT("SetRenderState() failed!"));
}

void set_texture_stage_state(const sge::d3d9::d3d_device_ptr device, const sge::stage_type stage, const D3DTEXTURESTAGESTATETYPE state, const sge::renderer::int_type value)
{
	if(device->SetTextureStageState(static_cast<DWORD>(stage),state,value) != D3D_OK)
		throw sge::exception(SGE_TEXT("SetTextureStageState() failed!"));
}

void set_sampler_state(const sge::d3d9::d3d_device_ptr device, const sge::stage_type stage, const D3DSAMPLERSTATETYPE state, const sge::renderer::int_type value)
{
	if(device->SetSamplerState(static_cast<DWORD>(stage),state,value) != D3D_OK)
		throw sge::exception(SGE_TEXT("SetSamplerState() failed!"));
}

void set_texture(const sge::d3d9::d3d_device_ptr device, const sge::stage_type stage, IDirect3DBaseTexture9* const tex)
{
	if(device->SetTexture(static_cast<DWORD>(stage),tex) != D3D_OK)
		throw sge::exception(SGE_TEXT("SetTexture() failed!"));
}

void set_transform(const sge::d3d9::d3d_device_ptr device, const D3DTRANSFORMSTATETYPE type, const sge::math::space_matrix& m)
{
	if(device->SetTransform(type, reinterpret_cast<const D3DMATRIX*>(m.data())) != D3D_OK)
		throw sge::exception(SGE_TEXT("SetTransform() failed!"));
}

}
