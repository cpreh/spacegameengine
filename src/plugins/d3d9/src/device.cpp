/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../create_caps.hpp"
#include "../create_device.hpp"
#include "../index_buffer.hpp"
#include "../offscreen_target.hpp"
#include "../onscreen_target.hpp"
#include "../vertex_buffer.hpp"
#include "../vertex_declaration.hpp"
#include "../convert/indexed_primitive.hpp"
#include "../convert/nonindexed_primitive.hpp"
#include "../devicefuncs/set_material.hpp"
#include "../devicefuncs/set_stream_source.hpp"
#include "../devicefuncs/set_transform.hpp"
#include "../parameters/create.hpp"
#include "../state/visitor.hpp"
#include "../texture/cube.hpp"
#include "../texture/planar.hpp"
#include "../texture/volume.hpp"
#include <sge/renderer/exception.hpp>
#include <sge/renderer/nonindexed_primitive_count.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/viewport.hpp>
#include <sge/renderer/state/default.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/time/millisecond.hpp>
#include <sge/time/sleep.hpp>
#include <sge/window/instance.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt//make_shared_ptr.hpp>
#include <boost/foreach.hpp>
#include <algorithm>

sge::d3d9::device::device(
	IDirect3D9 *const _system,
	renderer::adapter const _adapter,
	renderer::parameters const &_parameters,
	window::instance_ptr const _window
)
:
	present_parameters_(
		d3d9::parameters::create(
			_parameters,
			_window
		)
	),
	device_(
		d3d9::create_device(
			_system,
			_adapter,
			present_parameters_
		)
	),
	window_(_window),
	caps_(
		d3d9::create_caps(
			_system,
			_adapter
		)
	),
	resources_(),
	onscreen_target_(
		fcppt::make_shared_ptr<
			d3d9::onscreen_target
		>(
			device_.get(),
			sge::renderer::viewport(
				sge::renderer::pixel_rect(
					sge::renderer::pixel_rect::vector::null(),
					fcppt::math::dim::structure_cast<
						sge::renderer::pixel_rect::dim
					>(
						_window->size()
					)
				)
			)	
		)
	),
	offscreen_target_(),
	target_(
		onscreen_target_
	),
	clear_state_()
{
	this->state(
		sge::renderer::state::default_()
	);
}

sge::d3d9::device::~device()
{
}

void
sge::d3d9::device::begin_rendering()
{
	if(
		device_->Clear(
			0,
			0,
			clear_state_.flags(),
			clear_state_.color(),
			clear_state_.depth(),
			clear_state_.stencil()
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("Clear() failed!")
		);

	if(
		device_->BeginScene()
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("BeginScene() failed!")
		);
}

void
sge::d3d9::device::end_rendering()
{
	if(
		device_->EndScene()
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("EndScene() failed!")
		);

	switch(
		device_->Present(
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
		this->reset();
		break;
	default:
		throw sge::renderer::exception(
			FCPPT_TEXT("Present() failed!")
		);
	}
}

void
sge::d3d9::device::render(
	renderer::const_index_buffer_ptr const _index_buffer,
	renderer::first_vertex const _first_vertex,
	renderer::vertex_count const _num_vertices,
	renderer::indexed_primitive_type::type const _primitive_type,
	renderer::primitive_count const _primitive_count,
	renderer::first_index const _first_index
)
{
	this->set_index_buffer(
		_index_buffer
	);

	if(
		device_->DrawIndexedPrimitive(
			convert::indexed_primitive(
				_primitive_type
			),
			0,
			static_cast<
				UINT
			>(
				_first_vertex.get()
			),
			static_cast<
				UINT
			>(
				_num_vertices.get()
			),
			static_cast<
				UINT
			>(
				_first_index.get()
			),
			static_cast<
				UINT
			>(
				_primitive_count.get()
			)
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("DrawIndexedPrimitive() failed!")
		);
}

void
sge::d3d9::device::render(
	renderer::first_vertex const _first_vertex,
	renderer::vertex_count const _num_vertices,
	renderer::nonindexed_primitive_type::type const _primitive_type
)
{
	if(
		device_->DrawPrimitive(
			convert::nonindexed_primitive(
				_primitive_type
			),
			static_cast<
				UINT
			>(
				_first_vertex.get()
			),
			static_cast<
				UINT
			>(
				sge::renderer::nonindexed_primitive_count(
					_num_vertices,
					_primitive_type
				)
			)
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("DrawPrimitive() failed!")
		);
}

void
sge::d3d9::device::activate_vertex_buffer(
	renderer::const_vertex_buffer_ptr const _buffer
)
{
	d3d9::devicefuncs::set_stream_source(
		device_.get(),
		_buffer->format_part_index(),
		dynamic_cast<
			d3d9::vertex_buffer const &
		>(
			*_buffer
		).get(),
		_buffer->format_part().stride()
	);
}

void
sge::d3d9::device::deactivate_vertex_buffer(
	renderer::const_vertex_buffer_ptr const _buffer
)
{
}

void
sge::d3d9::device::vertex_declaration(
	renderer::const_vertex_declaration_ptr const _declaration
)
{
	if(
		!_declaration
	)
		return;

	if(
		device_->SetVertexDeclaration(
			dynamic_cast<
				d3d9::vertex_declaration const &
			>(
				*_declaration
			).get()
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("SetVertexDeclaration() failed!")
		);
}

void
sge::d3d9::device::state(
	renderer::state::list const &_states
)
{
	d3d9::state::visitor const visitor(
		device_.get(),
		clear_state_
	);

	BOOST_FOREACH(
		sge::renderer::state::list::set_type::const_reference ref,
		_states.values()
	)
		fcppt::variant::apply_unary(
			visitor,
			ref
		);
}

void
sge::d3d9::device::push_state(
	renderer::state::list const &_states
)
{
}

void
sge::d3d9::device::pop_state()
{
}

void
sge::d3d9::device::material(
	renderer::material const &_material
)
{
	d3d9::devicefuncs::set_material(
		device_.get(),
		_material
	);
}

void
sge::d3d9::device::enable_light(
	renderer::light_index const _index,
	bool const _enable
)
{
}

void
sge::d3d9::device::light(
	renderer::light_index const _index,
	renderer::light const &_light
)
{
}

void
sge::d3d9::device::enable_clip_plane(
	renderer::clip_plane_index const _index,
	bool const _enable
)
{
}

void
sge::d3d9::device::clip_plane(
	renderer::clip_plane_index const _index,
	renderer::clip_plane const &_plane
)
{
}

void
sge::d3d9::device::scissor_area(
	renderer::scissor_area const &_area
)
{
}

void
sge::d3d9::device::sampler_stage_op(
	renderer::stage_type const _stage,
	renderer::sampler_stage_op::type const _type,
	renderer::sampler_stage_op_value::type const _arg
)
{
#if 0
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
#endif
}

void
sge::d3d9::device::sampler_stage_arg(
	renderer::stage_type const _stage,
	renderer::sampler_stage_arg::type const _type,
	renderer::sampler_stage_arg_value::type const _arg
)
{
#if 0
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
#endif
}

void
sge::d3d9::device::texture(
	renderer::texture::const_base_ptr const _texture,
	renderer::stage_type const _stage
)
{
	if(
		device_->SetTexture(
			static_cast<
				DWORD
			>(
				_stage.get()
			),
			_texture
			?
				dynamic_cast<
					d3d9::texture::base const &
				>(
					*_texture
				).get()
			:
				0
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("SetTexture() failed!")
		);
}

void
sge::d3d9::device::transform(
	renderer::matrix_mode::type const _mode,
	renderer::matrix4 const &_matrix
)
{
	d3d9::devicefuncs::set_transform(
		device_.get(),
		_mode,
		_matrix
	);
}

void
sge::d3d9::device::target(
	renderer::target_ptr const _target
)
{
	if(
		_target == offscreen_target_ 
	)
		return;

	if(
		target_
	)
		target_->active(
			false
		);
	
	offscreen_target_ =
		fcppt::dynamic_pointer_cast<
			d3d9::offscreen_target
		>(
			_target
		);
	
	target_ =
		offscreen_target_
		?
			d3d9::target_base_ptr(
				offscreen_target_
			)
		:
			d3d9::target_base_ptr(
				onscreen_target_
			);

	target_->active(
		true
	);
}

sge::renderer::glsl::program_ptr const
sge::d3d9::device::create_glsl_program()
{
	throw sge::renderer::exception(
		FCPPT_TEXT("glsl not supported for d3d9!")
	);
}

sge::renderer::glsl::vertex_shader_ptr const
sge::d3d9::device::create_glsl_vertex_shader(
	renderer::glsl::string const &
)
{
	throw sge::renderer::exception(
		FCPPT_TEXT("glsl not supported for d3d9!")
	);
}

sge::renderer::glsl::pixel_shader_ptr const
sge::d3d9::device::create_glsl_pixel_shader(
	renderer::glsl::string const &
)
{
	throw sge::renderer::exception(
		FCPPT_TEXT("glsl not supported for d3d9!")
	);
}

void
sge::d3d9::device::glsl_program(
	renderer::glsl::const_program_ptr
)
{
	throw sge::renderer::exception(
		FCPPT_TEXT("glsl not supported for d3d9!")
	);
}

sge::renderer::target_ptr const
sge::d3d9::device::create_target()
{
	return renderer::target_ptr();
}

sge::renderer::texture::planar_ptr const
sge::d3d9::device::create_planar_texture(
	renderer::texture::planar_parameters const &_param
)
{
	return
		this->add_resource<
			d3d9::texture::planar
		>(
			fcppt::make_shared_ptr<
				d3d9::texture::planar
			>(
				device_.get(),
				_param
			)
		);
}

sge::renderer::texture::depth_stencil_ptr const
sge::d3d9::device::create_depth_stencil_texture(
	renderer::dim2 const &_dim,
	renderer::depth_stencil_format::type const _format
)
{
	return renderer::texture::depth_stencil_ptr();
}

sge::renderer::depth_stencil_surface_ptr const
sge::d3d9::device::create_depth_stencil_surface(
	renderer::dim2 const &_dim,
	renderer::depth_stencil_format::type const _format
)
{
	return renderer::depth_stencil_surface_ptr();
}

sge::renderer::texture::volume_ptr const
sge::d3d9::device::create_volume_texture(
	renderer::texture::volume_parameters const &_param
)
{
	return
		this->add_resource<
			d3d9::texture::volume
		>(
			fcppt::make_shared_ptr<
				d3d9::texture::volume
			>(
				device_.get(),
				_param
			)
		);
}

sge::renderer::texture::cube_ptr const
sge::d3d9::device::create_cube_texture(
	renderer::texture::cube_parameters const &_param
)
{
	return
		this->add_resource<
			d3d9::texture::cube
		>(
			fcppt::make_shared_ptr<
				d3d9::texture::cube
			>(
				device_.get(),
				_param
			)
		);
}

sge::renderer::vertex_declaration_ptr const
sge::d3d9::device::create_vertex_declaration(
	renderer::vf::dynamic::format const &_format
)
{
	return
		fcppt::make_shared_ptr<
			d3d9::vertex_declaration
		>(
			device_.get(),
			_format
		);
}

sge::renderer::vertex_buffer_ptr const
sge::d3d9::device::create_vertex_buffer(
	renderer::vertex_declaration_ptr const _declaration,
	renderer::vf::dynamic::part_index const _part,
	renderer::size_type const _size,
	renderer::resource_flags_field const &_resource_flags
)
{
	return
		this->add_resource<
			d3d9::vertex_buffer
		>(
			fcppt::make_shared_ptr<
				d3d9::vertex_buffer
			>(
				device_.get(),
				dynamic_cast<
					d3d9::vertex_declaration const &
				>(
					*_declaration
				).format().parts().at(
					_part.get()
				),
				_part,
				_size,
				_resource_flags
			)
		);
}

sge::renderer::index_buffer_ptr const
sge::d3d9::device::create_index_buffer(
	renderer::index::dynamic::format::type const _format,
	renderer::size_type const _size,
	renderer::resource_flags_field const &_resource_flags
)
{
	return
		this->add_resource<
			d3d9::index_buffer
		>(
			fcppt::make_shared_ptr<
				d3d9::index_buffer
			>(
				device_.get(),
				_format,
				_size,
				_resource_flags
			)
		);
}

sge::renderer::onscreen_target_ptr const
sge::d3d9::device::onscreen_target() const
{
	return onscreen_target_;
}

sge::renderer::scissor_area const
sge::d3d9::device::scissor_area() const
{
	return
		renderer::scissor_area(
			renderer::scissor_area::value_type::null()
		);
}

sge::renderer::target_ptr const
sge::d3d9::device::target() const
{
	return offscreen_target_;
}

sge::renderer::matrix4 const
sge::d3d9::device::transform(
	renderer::matrix_mode::type const _mode
)
{
	return renderer::matrix4::identity();
}

sge::renderer::caps const
sge::d3d9::device::caps() const
{
	return caps_;
}

sge::window::instance_ptr const
sge::d3d9::device::window() const
{
	return window_;
}

template<
	typename Ptr
>
fcppt::shared_ptr<
	Ptr
> const
sge::d3d9::device::add_resource(
	fcppt::shared_ptr<
		Ptr
	> const _ptr
)
{
	resources_.push_back(
		*_ptr
	);

	return _ptr;
}

void
sge::d3d9::device::reinit_resources()
{
#if 0
	IDirect3DSurface9 *surface;

	if(device->GetRenderTarget(0,&surface) != D3D_OK)
		throw exception(FCPPT_TEXT("d3d: cannot obtain default render target!"));

	default_render_target.reset(surface);

#endif
	std::for_each(
		resources_.begin(),
		resources_.end(),
		std::tr1::bind(
			&resource::reset,
			std::tr1::placeholders::_1
		)
	);
}

void
sge::d3d9::device::release_resources()
{
	std::for_each(
		resources_.begin(),
		resources_.end(),
		std::tr1::bind(
			&resource::loss,
			std::tr1::placeholders::_1
		)
	);

#if 0
	default_render_target.reset();

	vertex_declaration.reset();
#endif
}

void
sge::d3d9::device::set_index_buffer(
	sge::renderer::const_index_buffer_ptr const _buffer
)
{
	d3d9::index_buffer const &d3d_buffer(
		dynamic_cast<
			d3d9::index_buffer const &
		>(
			*_buffer
		)
	);

	if(
		device_->SetIndices(
			d3d_buffer.get()
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("set_index_buffer() failed")
		);
}

void
sge::d3d9::device::reset()
{
	this->release_resources();

	while(
		device_->TestCooperativeLevel()
		== D3DERR_DEVICELOST
	)
		sge::time::sleep(
			sge::time::millisecond(
				1
			)
		);

	switch(
		device_->Reset(
			&present_parameters_
		)
	)
	{
	case D3D_OK:
		this->reinit_resources();
		break;
	case D3DERR_DEVICELOST:
		throw sge::renderer::exception(
			FCPPT_TEXT("d3d device still lost!")
		);
	case D3DERR_DRIVERINTERNALERROR:
		throw sge::renderer::exception(
			FCPPT_TEXT("d3d driver internal error!")
		);
	case D3DERR_INVALIDCALL:
		throw sge::renderer::exception(
			FCPPT_TEXT("d3d invalid call to reset!")
		);
	default:
		throw sge::renderer::exception(
			FCPPT_TEXT("d3d reset failed!")
		);
	}
}

#if 0

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
		throw sge::exception(FCPPT_TEXT("SetRenderState() failed!"));
}

void set_render_state(const sge::d3d9::d3d_device_ptr device, const D3DRENDERSTATETYPE state, const sge::renderer::int_type value)
{
	if(device->SetRenderState(state,value) != D3D_OK)
		throw sge::exception(FCPPT_TEXT("SetRenderState() failed!"));
}

void set_render_state(const sge::d3d9::d3d_device_ptr device, const D3DRENDERSTATETYPE state, const sge::renderer::float_type value)
{
	if(device->SetRenderState(state,reinterpret_cast<const DWORD&>(value)) != D3D_OK)
		throw sge::exception(FCPPT_TEXT("SetRenderState() failed!"));
}

void set_texture_stage_state(const sge::d3d9::d3d_device_ptr device, const sge::stage_type stage, const D3DTEXTURESTAGESTATETYPE state, const sge::renderer::int_type value)
{
	if(device->SetTextureStageState(static_cast<DWORD>(stage),state,value) != D3D_OK)
		throw sge::exception(FCPPT_TEXT("SetTextureStageState() failed!"));
}

void set_sampler_state(const sge::d3d9::d3d_device_ptr device, const sge::stage_type stage, const D3DSAMPLERSTATETYPE state, const sge::renderer::int_type value)
{
	if(device->SetSamplerState(static_cast<DWORD>(stage),state,value) != D3D_OK)
		throw sge::exception(FCPPT_TEXT("SetSamplerState() failed!"));
}

void set_render_target(const sge::d3d9::d3d_device_ptr device, const sge::d3d9::d3d_surface_ptr target)
{
		if(device->SetRenderTarget(0, target.get()) != D3D_OK)
			throw sge::exception(FCPPT_TEXT("SetRenderTarget() failed!"));
}

}
#endif
