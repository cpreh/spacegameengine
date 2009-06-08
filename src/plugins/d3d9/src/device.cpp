/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../device.hpp"
#include "../texture.hpp"
//#include "../volume_texture.hpp"
#include "../cube_texture.hpp"
#include "../vertex_buffer.hpp"
#include "../index_buffer.hpp"
#include "../target.hpp"
#include "../material.hpp"
#include <sge/renderer/parameters.hpp>
#include <sge/stub.hpp>
#include <sge/bit.hpp>
#include <sge/exception.hpp>
#include <sge/make_shared_ptr.hpp>
#include <boost/bind.hpp>
#include <algorithm>

namespace
{

void set_render_state(sge::d3d9::d3d_device_ptr device, D3DRENDERSTATETYPE state, sge::renderer::bool_type value);
void set_render_state(sge::d3d9::d3d_device_ptr Device, D3DRENDERSTATETYPE state, sge::renderer::int_type value);
void set_render_state(sge::d3d9::d3d_device_ptr device, D3DRENDERSTATETYPE state, sge::renderer::float_type value);
void set_sampler_state(sge::d3d9::d3d_device_ptr device, sge::stage_type stage, D3DSAMPLERSTATETYPE state, sge::renderer::int_type value);
void set_texture(sge::d3d9::d3d_device_ptr device, sge::stage_type stage, IDirect3DBaseTexture9* tex);
void set_texture_stage_state(sge::d3d9::d3d_device_ptr device, sge::stage_type stage, D3DTEXTURESTAGESTATETYPE state, sge::renderer::int_type value);
void set_transform(sge::d3d9::d3d_device_ptr device, D3DTRANSFORMSTATETYPE, const sge::math::space_matrix&);
void set_render_target(sge::d3d9::d3d_device_ptr device, sge::d3d9::d3d_surface_ptr target);

}

sge::d3d9::device::device(
	d3d_device_ptr const device,
	renderer::parameters const &param,
	D3DPRESENT_PARAMETERS const &present_parameters,
	windows::window_ptr const window_,
	renderer::caps const &caps_)
:
	device(device),
	screen_size_(param.mode().size()),
	preset_parameters(present_parameters),
	window_(window_),
	caps_(caps_)
{
	init();
}

void
sge::d3d9::device::begin_rendering()
{
	if(
		device->Clear(
			0,
			0,
			clear_flags,
			clear_color,
			zbuffer_clear_val,
			stencil_clear_val
		) != D3D_OK
	)
		throw exception(
			SGE_TEXT("Clear() failed!")
		);

	if(device->BeginScene() != D3D_OK)
		throw exception(SGE_TEXT("BeginScene() failed!"));
}

void
sge::d3d9::device::end_rendering()
{
	if(device->EndScene() != D3D_OK)
		throw exception(SGE_TEXT("EndScene() failed!"));

	switch(
		device->Present(
			0,
			0,
			0,
			0
		)
	)
	{
	case D3D_OK:
		break;
	case D3DERR_DEVICELOST:
		reset();
		break;
	default:
		throw exception(
			SGE_TEXT("Present() failed!")
		);
	}
}

void
sge::d3d9::device::render(
	renderer::const_vertex_buffer_ptr const vb,
	renderer::const_index_buffer_ptr const ib,
	renderer::size_type const first_vertex,
	renderer::size_type const num_vertices,
	renderer::indexed_primitive_type::type const ptype,
	renderer::size_type const primitive_count,
	renderer::size_type const first_index)
{
	D3DPRIMITIVETYPE const prim_type(
		convert_indexed_primitive(
			ptype
		)
	);

	if(vb != nvb)
		set_vertex_buffer(nvb);

	if(ib != nib)
		set_index_buffer(nib);

	if(
		device->DrawIndexedPrimitive(
			prim_type,
			0,
			static_cast<UINT>(first_vertex),
			static_cast<UINT>(num_vertices),
			static_cast<UINT>(first_index),
			static_cast<UINT>(primitive_count)
		) != D3D_OK
	)
		throw exception(SGE_TEXT("DrawIndexedPrimitive() failed!"));
}

void
sge::d3d9::device::render(
	renderer::const_vertex_buffer_ptr const vb,
	renderer::size_type const first_vertex,
	renderer::size_type const num_vertices,
	renderer::nonindexed_primitive_type::type const ptype)
{
	D3DPRIMITIVETYPE const prim_type(
		convertex_nonindexed_primitive(
			ptype
		)
	);

	if(vb != nvb)
		set_vertex_buffer(nvb);

	if(
		device->DrawPrimitive(
			prim_type,
			static_cast<UINT>(first_vertex),
			static_cast<UINT>(
				primitive_count(
					num_vertices,
					ptype
				)
			)
		) != D3D_OK
	)
		throw exception(SGE_TEXT("DrawPrimitive() failed!"));
}

void
sge::d3d9::device::state(
	renderer::state::list const &states)
{
}

void
sge::d3d9::device::push_state(
	renderer::state::list const &states)
{
}

void
sge::d3d9::device::pop_state()
{
}

void
sge::d3d9::device::material(
	renderer::material const &mat)
{
	set_material(
		device,
		mat
	);
}

void
sge::d3d9::device::enable_light(
	renderer::light_index const index,
	bool const enable)
{
}

void
sge::d3d9::device::light(
	renderer::light_index const index,
	renderer::light const &light_)
{
}

void
sge::d3d9::device::texture_stage_op(
	renderer::stage_type const stage,
	renderer::texture_stage_op::type const type,
	renderer::texture_stage_op_value::type const arg)
{
	set_texture_stage_state(
		device,
		stage,
		convert_texture_stage_op(
			type
		),
		convert_texture_stage_op_value(
			value
		)
	);
}

void
sge::d3d9::device::texture_stage_arg(
	renderer::stage_type const stage,
	renderer::texture_stage_arg::type const type,
	renderer::texture_stage_arg_value::type const arg)
{
	set_texture_stage_state(
		device,
		stage,
		convert_texture_arg(
			type
		),
		convert_texture_arg_value(
			arg
		)
	);
}

void
sge::d3d9::device::texture(
	renderer::const_texture_base_ptr const tex,
	renderer::stage_type const stage)
{
	set_texture(
		device,
		stage,
		tex
		?
			dynamic_cast<
				texture_base const &
			>(*tex).base()
		:
			0
	);
}

void
sge::d3d9::device::transform(
	renderer::any_matrix const &mat)
{
	set_transform(
		device_,
		D3DTS_WORLD,
		math
	);
}

void
sge::d3d9::device::projection(
	renderer::any_matrix const &mat)
{
	set_transform(
		device_,
		D3DTS_PROJECTION,
		math
	);
}

void
sge::d3d9::device::texture_transform(
	renderer::any_matrix const &mat)
{
	set_transform(
		device_,
		D3DTS_TEXTURE,
		math
	);
}

void
sge::d3d9::device::target(
	renderer::texture_ptr const tex)
{
}

void
sge::d3d9::device::viewport(
	renderer::viewport const &vp)
{
}

void
sge::d3d9::device::viewport_mode(
	renderer::viewport_mode::type const vm)
{
}

sge::renderer::glsl::program_ptr const
sge::d3d9::device::create_glsl_program(
	renderer::glsl::optional_string const &,
	renderer::glsl::optional_string const &)
{
	throw exception(
		SGE_TEXT("glsl not supported for d3d9!")
	);
}

sge::renderer::glsl::program_ptr const
sge::d3d9::device::create_glsl_program(
	renderer::glsl::optional_istream const &,
	renderer::glsl::optional_istream const &)
{
	return create_glsl_program(
		renderer::glsl::optional_string(),
		renderer::glsl::optional_string()
	);
}

void
sge::d3d9::device::glsl_program(
	renderer::glsl::program_ptr)
{
	// TODO: throw here, too!
}

sge::renderer::const_target_ptr const
sge::d3d9::device::target() const
{
	return target_;
}

sge::renderer::texture_ptr const
sge::d3d9::device::create_texture(
	renderer::dim_type const &dim,
	image::color::format::type const format,
	renderer::filter::texture const &filter,
	renderer::resource_flag_t const flags)
{
	return add_resource(
		make_shared_ptr<
			texture
		>(
			device,
			data,
			dim,
			filter,
			flags
		)
	);
}

	/*const volume_texture_ptr create_volume_texture(
		volume_texture::image_view_array const &,
		filter::texture const &filter,
		resource_flag_t flags);*/

sge::renderer::cube_texture_ptr const
sge::d3d9::device::create_cube_texture(
	renderer::size_type const border_size,
	image::color::format::type const format,
	renderer::filter::texture const &filter,
	renderer::resource_flag_t const flags)
{
	return add_resource(
		make_shared_ptr<
			cube_texture
		>(
			device,
			src,
			size,
			filter,
			flags
		)
	);
}

sge::renderer::vertex_buffer_ptr const
sge::d3d9::device::create_vertex_buffer(
	renderer::vf::dynamic_format const &format,
	renderer::size_type const size,
	renderer::resource_flag_t const flags)
{
	return add_resource(
		make_shared_ptr<
			vertex_buffer
		>(
			device,
			format,
			size,
			flags
		)
	);
}

sge::renderer::index_buffer_ptr const
sge::d3d9::device::create_index_buffer(
	renderer::index::format::type const type,
	renderer::size_type const size,
	renderer::resource_flag_t const flags)
{
	return add_resource(
		make_shared_ptr<
			index_buffer
		>(
			device,
			size,
			flags,
		)
	);
}

sge::renderer::caps const
sge::d3d9::device::caps() const
{
	return caps_;
}

sge::renderer::screen_size const
sge::d3d9::device::screen_size() const
{
	return param.mode().size();
}

sge::window::instance_ptr const
sge::d3d9::device::window() const
{
	return window_;
}

template<
	typename Ptr
>
Ptr const
sge::d3d9::device::add_resource(
	Ptr const ptr)
{
	resources.push_back(
		*ptr
	);
	return ptr;
}

void sge::d3d9::device::init()
{
	IDirect3DSurface9 *surface;

	if(device->GetRenderTarget(0,&surface) != D3D_OK)
		throw exception(SGE_TEXT("d3d: cannot obtain default render target!"));

	default_render_target.reset(surface);

	std::for_each(
		resources.begin(),
		resources.end(),
		boost::bind(
			&resource::on_reset,
			_1
		)
	);
}

void sge::d3d9::renderer::release_resources()
{
	std::for_each(
		resources.begin(),
		resources.end(),
		boost::bind(
			&resource::on_loss,
			_1
		)
	);

	default_render_target.reset();

	vertex_declaration.reset();
}

/*
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
*/

const sge::render_target_ptr sge::d3d9::renderer::create_render_target(
	const render_target::dim_type& dim)
{
	return render_target_ptr(
		new render_target(
			*this,
			device,
			dim));
}

void
sge::d3d9::device::set_vertex_buffer(
	renderer::const_vertex_buffer_ptr const buffer)
{
	if(!buffer)
		return; //FIXME

	vertex_buffer const &d3d_buffer(
		dynamic_cast<
			vertex_buffer const &
		>(*buffer)
	);

	d3d_vertex_declaration_ptr const decl(
		d3d_buffer.d3d_format.vertex_declaration()
	);

	if(decl != vertex_declaration)
	{
		if(
			device->SetVertexDeclaration(
				decl.get()
			) != D3D_OK
		)
			throw exception(SGE_TEXT("set_vertex_declaration() failed"));

		vertex_declaration = decl;
	}

	if(
		device->SetStreamSource(
			0,
			d3d_buffer.buffer.get(),
			0,
			static_cast<UINT>(
				->stride()
			)
		) != D3D_OK
	)
		throw exception(SGE_TEXT("set_vertex_buffer() failed"));
}

void
sge::d3d9::device::set_index_buffer(
	renderer::const_index_buffer_ptr const buffer)
{
	if(!buffer)
		return; //FIXME

	index_buffer const &d3d_buffer(
		dynamic_cast<
			index_buffer const &
		>(*buffer)
	);

	if(
		device->SetIndices(
			d3d_buffer.buffer.get()
		) != D3D_OK
	)
		throw exception(SGE_TEXT("set_index_buffer() failed"));
}

void sge::d3d9::renderer::set_render_target(const texture_ptr target)
{
	if(!target)
	{
		::set_render_target(device, default_render_target);
		return;
	}

	render_target& d3d_target = dynamic_cast<render_target&>(*target);

	::set_render_target(device, d3d_target.surface);
}

void sge::d3d9::device::reset()
{
	release_resources();

	while(device->TestCooperativeLevel() == D3DERR_DEVICELOST)
		sge::time::sleep(
			sge::time::millisecond(
				1
			)
		);

	switch(
		device->reset(
			&present_parameters
		)
	)
	{
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

/*void sge::d3d9::renderer::set_filter_state(const stage_type stage, const filter_arg type, const filter_arg_value value)
{
	const D3DSAMPLERSTATETYPE d3d_type = convert_cast<D3DSAMPLERSTATETYPE>(type);
	const D3DTEXTUREFILTERTYPE d3d_value = convert_cast<D3DTEXTUREFILTERTYPE>(value);
	set_sampler_state(device,stage,d3d_type,d3d_value);
}*/

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
	
	//set_sampler_state(device,stage,d3d_type,d3d_value);
}

void set_render_target(const sge::d3d9::d3d_device_ptr device, const sge::d3d9::d3d_surface_ptr target)
{
		if(device->SetRenderTarget(0, target.get()) != D3D_OK)
			throw sge::exception(SGE_TEXT("SetRenderTarget() failed!"));
}

}
