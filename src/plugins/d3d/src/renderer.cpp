/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <iterator>
#include <algorithm>
#include <functional>
#include "../../../ptr_cast.hpp"
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

#include <iostream>

namespace
{
	void set_render_state(sge::d3d::d3d_device_ptr device, D3DRENDERSTATETYPE state, sge::bool_type value);
	void set_render_state(sge::d3d::d3d_device_ptr Device, D3DRENDERSTATETYPE state, sge::int_type value);
	void set_render_state(sge::d3d::d3d_device_ptr device, D3DRENDERSTATETYPE state, sge::float_type value);
	void set_sampler_state(sge::d3d::d3d_device_ptr device, sge::stage_type stage, D3DSAMPLERSTATETYPE state, sge::int_type value);
	void set_texture(sge::d3d::d3d_device_ptr device, sge::stage_type stage, IDirect3DBaseTexture9* tex);
	void set_texture_stage_state(sge::d3d::d3d_device_ptr device, sge::stage_type stage, D3DTEXTURESTAGESTATETYPE state, sge::int_type value);
}

sge::d3d::renderer::renderer(const d3d_device_ptr device, const renderer_parameters& param, const int adapter, const win32_window_ptr wnd, const d3d_ptr sys)
: sys(sys),
  device(device),
  adapter(adapter),
  parameters(param),
  render_window(wnd),
  clear_zbuffer(true),
  clear_stencil(false),
  clear_back_buffer(true),
  clear_color(static_rgba<255,255,255,255>::value), // FIXME (should be argb)
  stencil_clear_val(0),
  zbuffer_clear_val(1.f)
{
	create_renderer_caps(adapter,sys,_caps);
	init();
}

void sge::d3d::renderer::init()
{
	IDirect3DSurface9* surface;
	if(device->GetRenderTarget(0,&surface) != D3D_OK)
		throw std::runtime_error("d3d: cannot obtain default render target!");
	default_render_target.reset(surface);
	std::for_each(resources.begin(),resources.end(),std::mem_fun(&resource::on_reset));
}

void sge::d3d::renderer::release_resources()
{
	std::for_each(resources.begin(),resources.end(),std::mem_fun(&resource::on_loss));
	default_render_target.reset();
	vertex_declaration.reset();
}

sge::vertex_buffer_ptr sge::d3d::renderer::create_vertex_buffer(const sge::vertex_format& format, const vertex_buffer::size_type size, const resource_flag_t flags, const vertex_buffer::const_pointer data)
{
	return vertex_buffer_ptr(new vertex_buffer(this,device,format,size,flags,data));
}

sge::index_buffer_ptr sge::d3d::renderer::create_index_buffer( const index_buffer::size_type size, const resource_flag_t flags, const index_buffer::const_pointer data)
{
	return index_buffer_ptr(new index_buffer(this,device,size,flags,data));
}

sge::texture_ptr sge::d3d::renderer::create_texture(const texture::const_pointer data, const texture::size_type width, const texture::size_type height, const unsigned mip_levels, const resource_flag_t flags)
{
	return texture_ptr(new texture(this,device,data,width,height,mip_levels,flags));
}

sge::volume_texture_ptr sge::d3d::renderer::create_volume_texture(const volume_texture::const_pointer data, const volume_texture::size_type width, const volume_texture::size_type height, const volume_texture::size_type depth, const resource_flag_t flags)
{
	return volume_texture_ptr(new volume_texture(this,device,data,width,height,depth,flags));
}

sge::cube_texture_ptr sge::d3d::renderer::create_cube_texture(const cube_side_array* const src, const cube_texture::size_type size, const resource_flag_t flags)
{
	return cube_texture_ptr(new cube_texture(this,device,src,size,flags));
}

sge::render_target_ptr sge::d3d::renderer::create_render_target(const render_target::size_type width, const render_target::size_type height)
{
	return render_target_ptr(new render_target(this,device,width,height));
}

sge::window_ptr sge::d3d::renderer::get_window() const
{
	return render_window;
}

void sge::d3d::renderer::set_vertex_buffer(const vertex_buffer_ptr buffer)
{
	if(!buffer)
		return;

	d3d::vertex_buffer* const d3d_buffer = ptr_cast<d3d::vertex_buffer*>(buffer.get());
	const d3d_vertex_declaration_ptr decl = d3d_buffer->d3d_format.vertex_declaration();
	if(decl != vertex_declaration)
	{
		if(device->SetVertexDeclaration(decl.get()) != D3D_OK)
			throw std::runtime_error("set_vertex_declaration() failed");
		vertex_declaration = decl;
	}
	if(device->SetStreamSource(0,d3d_buffer->buffer.get(),0,unsigned(buffer->stride())) != D3D_OK)
		throw std::runtime_error("set_vertex_buffer() failed");
}

void sge::d3d::renderer::set_index_buffer(const index_buffer_ptr buffer)
{
	if(!buffer)
		return;

	d3d::index_buffer* const d3d_buffer = ptr_cast<d3d::index_buffer*>(buffer.get());
	if(device->SetIndices(d3d_buffer->buffer.get()) != D3D_OK)
		throw std::runtime_error("set_index_buffer() failed");
}

void sge::d3d::renderer::set_render_target(const render_target_ptr target)
{
	if(!target)
	{
		if(device->SetRenderTarget(0,default_render_target.get()) != D3D_OK)
			throw std::runtime_error("cannot set default render target");
		return;
	}

	render_target* const d3d_target = ptr_cast<render_target*>(target.get());

	if(device->SetRenderTarget(0,d3d_target->surface.get()) != D3D_OK)
		throw std::runtime_error("cannot set texture as render target");
}

void sge::d3d::renderer::set_material(const material& m)
{
	if(device->SetMaterial(reinterpret_cast<const D3DMATERIAL9*>(&m)) != D3D_OK)
		throw std::runtime_error("set_material() failed");
}

void sge::d3d::renderer::reset(const renderer_parameters* const param)
{
	release_resources();

	if(param)
	{
		if(parameters.mode.width != param->mode.width ||
		   parameters.mode.height != param->mode.height)
		{
			render_window->size(window::window_size(param->mode.width,param->mode.height));
			parameters.mode = param->mode;
		}
		parameters.samples = param->samples;
		parameters.windowed = param->windowed;
		parameters.vsync = param->vsync;
	}

	D3DPRESENT_PARAMETERS pp = create_present_parameters(parameters,adapter,render_window,sys);

	while(device->TestCooperativeLevel() == D3DERR_DEVICELOST)
	{
		//sge::process_window_msgs();
		sge::sleep(10);
	}

	const HRESULT reset_res = device->Reset(&pp);
	switch(reset_res) {
	case D3D_OK:
		init();
		break;
	case D3DERR_DEVICELOST:
		throw std::runtime_error("d3d device still lost");
	case D3DERR_DRIVERINTERNALERROR:
		throw std::runtime_error("d3d driver internal error");
	case D3DERR_INVALIDCALL:
		throw std::runtime_error("d3d invalid call to reset");
	default:
		throw std::runtime_error("d3d reset failed");
	}
}

void sge::d3d::renderer::set_texture(const stage_type stage, const texture_base_ptr p)
{
	if(!p)
		return ::set_texture(device,stage,0);

	texture_base* const tex_base = ptr_cast<texture_base*>(p.get());
	::set_texture(device,stage,tex_base->base);
}

void sge::d3d::renderer::set_texture_stage_op(const stage_type stage, const stage_op type, const stage_op_value value)
{
	const D3DTEXTURESTAGESTATETYPE d3d_type = convert_cast<D3DTEXTURESTAGESTATETYPE>(type);
	const DWORD d3d_value = convert_cast<DWORD>(value);
	set_texture_stage_state(device,stage,d3d_type,d3d_value);
}

void sge::d3d::renderer::set_texture_stage_arg(const stage_type stage, const stage_arg type, const stage_arg_value value)
{
	const D3DTEXTURESTAGESTATETYPE d3d_type = convert_cast<D3DTEXTURESTAGESTATETYPE>(type);
	const DWORD d3d_value = convert_cast<DWORD>(value);
	set_texture_stage_state(device,stage,d3d_type,d3d_value);
}

void sge::d3d::renderer::set_filter_state(const stage_type stage, const filter_arg type, const filter_arg_value value)
{
	const D3DSAMPLERSTATETYPE d3d_type = convert_cast<D3DSAMPLERSTATETYPE>(type);
	const D3DTEXTUREFILTERTYPE d3d_value = convert_cast<D3DTEXTUREFILTERTYPE>(value);
	set_sampler_state(device,stage,d3d_type,d3d_value);
}

void sge::d3d::renderer::render(const vertex_buffer_ptr nvb, const index_buffer_ptr nib, const unsigned first_vertex, const unsigned num_vertices, const primitive_type ptype, const unsigned pcount, const unsigned first_index)
{
	const D3DPRIMITIVETYPE prim_type = convert_cast<D3DPRIMITIVETYPE>(ptype);
	if(vb != nvb)
		set_vertex_buffer(nvb);

	switch(ptype) {
	case PT_Line:
	case PT_Triangle:
		if(ib != nib)
			set_index_buffer(nib);
		if(device->DrawIndexedPrimitive(prim_type,0,first_vertex,num_vertices,first_index,pcount) != D3D_OK)
			throw std::runtime_error("DrawIndexedPrimitive() failed");
		break;
	case PT_Point:
	case PT_LineStrip:
	case PT_TriangleStrip:
	case PT_TriangleFan:
		if(device->DrawPrimitive(prim_type,first_vertex,pcount) != D3D_OK)
			throw std::runtime_error("DrawPrimitive() failed");
		break;
	}
}

void sge::d3d::renderer::begin_rendering()
{
	DWORD clear_flags = 0;
	if(clear_zbuffer)
		clear_flags |= D3DCLEAR_ZBUFFER;
	if(clear_back_buffer)
		clear_flags |= D3DCLEAR_TARGET;
	if(clear_stencil)
		clear_flags |= D3DCLEAR_STENCIL;

	if(device->Clear(0,0,clear_flags,clear_color,zbuffer_clear_val,stencil_clear_val) != D3D_OK)
		throw std::runtime_error("Clear() failed");
	if(device->BeginScene() != D3D_OK)
		throw std::runtime_error("BeginScene() failed");
}

void sge::d3d::renderer::end_rendering()
{
	if(device->EndScene() != D3D_OK)
		throw std::runtime_error("EndScene() failed");

	const HRESULT present_res = device->Present(0,0,0,0);
	switch(present_res) {
	case D3D_OK:
		break;
	case D3DERR_DEVICELOST:
		// TODO: Handle DEVICELOST
	default:
		throw std::runtime_error("Present() failed");
	}
}

void sge::d3d::renderer::set_bool_state(const bool_state state, const bool_type value)
{
	switch(state) {
	case BS_ClearZBuffer:
		clear_zbuffer = value;
		break;
	case BS_ClearStencil:
		clear_stencil = value;
		break;
	case BS_ClearBackBuffer:
		clear_back_buffer = value;
		break;
	case BS_EnableFog:
		set_render_state(device,D3DRS_FOGENABLE,value);
		break;
	case BS_EnableRangeFog:
		set_render_state(device,D3DRS_RANGEFOGENABLE,value);
		break;
	case BS_EnableStencil:
		set_render_state(device,D3DRS_STENCILENABLE,value);
		break;
	case BS_EnableAlphaBlending:
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
	case BS_EnableZBuffer:
		set_render_state(device,D3DRS_ZENABLE,value);
		break;
	}
}

void sge::d3d::renderer::set_float_state(const float_state state, const float_type value)
{
	switch(state) {
	case FS_ZBufferClearVal:
		zbuffer_clear_val = value;
		break;
	case FS_FogStart:
		set_render_state(device,D3DRS_FOGSTART,value);
		break;
	case FS_FogEnd:
		set_render_state(device,D3DRS_FOGEND,value);
		break;
	case FS_FogDensity:
		set_render_state(device,D3DRS_FOGDENSITY,value);
		break;
	}
}

void sge::d3d::renderer::set_int_state(const int_state state, const int_type value)
{
	switch(state) {
	case IS_AmbientLightColor:
		set_render_state(device,D3DRS_AMBIENT,value);
		break;
	case IS_FogColor:
		set_render_state(device,D3DRS_FOGCOLOR,value);
		break;
	case IS_FogMode:
		set_render_state(device,D3DRS_FOGTABLEMODE,value);
		break;
	case IS_ClearColor:
		clear_color = value;
		break;
	case IS_StencilClearVal:
		stencil_clear_val = value;
		break;
	}
}

void sge::d3d::renderer::set_transformation(const matrix4x4<space_unit>& m)
{
	if(device->SetTransform(D3DTS_WORLD,reinterpret_cast<const D3DMATRIX*>(&m)) != D3D_OK)
		throw std::runtime_error("SetTransform() failed");
}

void sge::d3d::renderer::projection_perspective(const space_unit fov, const space_unit near, const space_unit far)
{
	std::cerr << "stub: d3d::renderer::projection_perspective\n";
}

void sge::d3d::renderer::projection_orthogonal()
{
	const matrix4x4<space_unit> m(matrix_orthogonal_xy<space_unit>());
	if(device->SetTransform(D3DTS_PROJECTION,reinterpret_cast<const D3DMATRIX*>(&m)) != D3D_OK)
		throw std::runtime_error("SetTransform() failed");
}

const sge::renderer_caps& sge::d3d::renderer::caps() const
{
	return _caps;
}

unsigned sge::d3d::renderer::screen_width() const
{
	return parameters.mode.width;
}

unsigned sge::d3d::renderer::screen_height() const
{
	return parameters.mode.height;
}

namespace
{
	void set_render_state(const sge::d3d::d3d_device_ptr device, const D3DRENDERSTATETYPE state, const sge::bool_type value)
	{
		if(device->SetRenderState(state,value) != D3D_OK)
			throw std::runtime_error("SetRenderState() failed");
	}

	void set_render_state(const sge::d3d::d3d_device_ptr device, const D3DRENDERSTATETYPE state, const sge::int_type value)
	{
		if(device->SetRenderState(state,value) != D3D_OK)
			throw std::runtime_error("SetRenderState() failed");
	}

	void set_render_state(const sge::d3d::d3d_device_ptr device, const D3DRENDERSTATETYPE state, const sge::float_type value)
	{
		if(device->SetRenderState(state,reinterpret_cast<const DWORD&>(value)) != D3D_OK)
			throw std::runtime_error("SetRenderState() failed");
	}

	void set_texture_stage_state(const sge::d3d::d3d_device_ptr device, const sge::stage_type stage, const D3DTEXTURESTAGESTATETYPE state, const sge::int_type value)
	{
		if(device->SetTextureStageState(stage,state,value) != D3D_OK)
			throw std::runtime_error("SetTextureStageState() failed");
	}

	void set_sampler_state(const sge::d3d::d3d_device_ptr device, const sge::stage_type stage, const D3DSAMPLERSTATETYPE state, const sge::int_type value)
	{
		if(device->SetSamplerState(stage,state,value) != D3D_OK)
			throw std::runtime_error("SetSamplerState() failed");
	}

	void set_texture(const sge::d3d::d3d_device_ptr device, const sge::stage_type stage, IDirect3DBaseTexture9* const tex)
	{
		if(device->SetTexture(stage,tex) != D3D_OK)
			throw std::runtime_error("SetTexture() failed");
	}
}
