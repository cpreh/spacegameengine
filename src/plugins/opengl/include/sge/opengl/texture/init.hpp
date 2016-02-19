/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_TEXTURE_INIT_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_INIT_HPP_INCLUDED

#include <sge/opengl/color_format.hpp>
#include <sge/opengl/color_format_type.hpp>
#include <sge/opengl/internal_color_format.hpp>
#include <sge/opengl/texture/basic_buffer_parameters.hpp>
#include <sge/opengl/texture/basic_parameters.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/check_dim.hpp>
#include <sge/opengl/texture/extend_size.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/opengl/texture/is_render_target.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/mipmap/create.hpp>
#include <sge/opengl/texture/mipmap/get_levels.hpp>
#include <sge/opengl/texture/mipmap/parameters.hpp>
#include <sge/renderer/basic_dim.hpp>
#include <sge/renderer/texture/capabilities.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/type_iso/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

template<
	typename Types
>
std::vector<
	fcppt::unique_ptr<
		typename
		Types::buffer_types::base
	>
>
init(
	sge::opengl::texture::binding const &_binding,
	sge::opengl::texture::basic_parameters const &_basic_parameters,
	typename Types::parameters const &_parameters,
	sge::opengl::texture::type const _type,
	sge::opengl::texture::buffer_type const _buffer_type,
	sge::opengl::texture::id const _id
)
{
	typedef
	sge::renderer::basic_dim<
		Types::buffer_types::dim_types::num_dims
	>
	extended_dim;

	typedef
	typename
	extended_dim::dim_wrapper
	dim_wrapper;

	extended_dim const size(
		sge::opengl::texture::extend_size(
			_parameters.size()
		)
	);

	sge::opengl::texture::check_dim<
		dim_wrapper::value
	>(
		size,
		Types::buffer_types::dim_types::min_size(),
		Types::name()
	);

	typedef
	typename
	Types::buffer_types::format_types::format
	format_type;

	format_type const format(
		Types::buffer_types::format_types::best_format(
			_parameters.format()
		)
	);

	format_type const gl_format(
		Types::buffer_types::format_types::translate_format(
			format,
			_parameters.format()
		)
	);

	sge::opengl::color_format const color_format(
		Types::buffer_types::format_types::convert_format()(
			gl_format
		)
	);

	sge::opengl::color_format_type const color_format_type(
		Types::buffer_types::format_types::convert_format_type()(
			gl_format
		)
	);

	sge::opengl::internal_color_format const internal_color_format(
		Types::buffer_types::format_types::convert_internal_format()(
			gl_format
		)
	);

	Types::buffer_types::dim_types::init_function()(
		_binding,
		_basic_parameters.context(),
		_buffer_type,
		color_format,
		color_format_type,
		internal_color_format,
		sge::renderer::texture::mipmap::level(
			0u
		),
		size,
		nullptr
	);

	sge::opengl::texture::mipmap::create<
		dim_wrapper::value
	>(
		sge::opengl::texture::mipmap::parameters<
			dim_wrapper::value
		>(
			_binding,
			_basic_parameters.context(),
			_buffer_type,
			color_format,
			color_format_type,
			internal_color_format,
			size,
			Types::buffer_types::dim_types::init_function()
		),
		_parameters.mipmap()
	);

	sge::renderer::texture::mipmap::level_count const mip_levels(
		sge::opengl::texture::mipmap::get_levels<
			dim_wrapper::value
		>(
			_parameters.mipmap(),
			size
		)
	);

	sge::opengl::texture::is_render_target const is_target(
		_parameters.capabilities()
		&
		sge::renderer::texture::capabilities::render_target
	);

	typedef
	typename
	Types::buffer_types::gl_buffer
	gl_buffer;

	typedef
	std::vector<
		fcppt::unique_ptr<
			typename
			Types::buffer_types::base
		>
	>
	level_container;

	return
		fcppt::algorithm::map<
			level_container
		>(
			fcppt::make_int_range_count(
				sge::renderer::texture::mipmap::level(
					mip_levels.get()
				)
			),
			[
				&_binding,
				&_basic_parameters,
				_type,
				_buffer_type,
				_id,
				&_parameters,
				color_format,
				color_format_type,
				format,
				internal_color_format,
				is_target
			](
				sge::renderer::texture::mipmap::level const _index
			)
			{
				return
					fcppt::unique_ptr_to_base<
						typename
						Types::buffer_types::base
					>(
						fcppt::make_unique_ptr<
							gl_buffer
						>(
							format,
							sge::opengl::texture::basic_buffer_parameters(
								_binding,
								_basic_parameters.context(),
								_index,
								_type,
								_buffer_type,
								_id,
								_parameters.resource_flags(),
								color_format,
								color_format_type,
								internal_color_format,
								is_target
							)
						)
					);
			}
		);
}

}
}
}

#endif
