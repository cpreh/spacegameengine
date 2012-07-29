/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_TEXTURE_BASIC_IMPL_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_IMPL_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/opengl/convert/color_to_format.hpp>
#include <sge/opengl/convert/color_to_format_type.hpp>
#include <sge/opengl/convert/color_to_internal_format.hpp>
#include <sge/opengl/texture/basic.hpp>
#include <sge/opengl/texture/basic_buffer.hpp>
#include <sge/opengl/texture/basic_parameters.hpp>
#include <sge/opengl/texture/best_color_format.hpp>
#include <sge/opengl/texture/check_dim.hpp>
#include <sge/opengl/texture/scoped_work_binding.hpp>
#include <sge/opengl/texture/funcs/get_parameter_int.hpp>
#include <sge/opengl/texture/mipmap/create.hpp>
#include <sge/opengl/texture/mipmap/get_levels.hpp>
#include <sge/opengl/texture/mipmap/parameters.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <sge/renderer/texture/mipmap/object.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/null_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>


template<
	typename Types
>
sge::opengl::texture::basic<
	Types
>::basic(
	sge::opengl::texture::basic_parameters const &_basic_parameters,
	sge::opengl::texture::type const _type,
	parameters_type const &_parameters
)
:
	sge::opengl::texture::base(
		_type
	),
	resource_flags_(
		_parameters.resource_flags()
	),
	capabilities_(
		_parameters.capabilities()
	),
	mipmap_(
		_parameters.mipmap()
	),
	levels_()
{
	sge::opengl::texture::check_dim<
		base_type::dim::dim_wrapper::value
	>(
		_parameters.size(),
		Types::min_size(),
		Types::name()
	);

	sge::opengl::texture::scoped_work_binding const binding(
		_basic_parameters.system_context(),
		this->type(),
		this->id()
	);

	sge::image::color::format::type const format(
		sge::opengl::texture::best_color_format(
			_parameters.format()
		)
	);

	sge::opengl::color_format const color_format(
		sge::opengl::convert::color_to_format(
			format
		)
	);

	sge::opengl::color_format_type const color_format_type(
		sge::opengl::convert::color_to_format_type(
			format
		)
	);

	sge::opengl::internal_color_format const internal_color_format(
		sge::opengl::convert::color_to_internal_format(
			format
		)
	);


	Types::init_function()(
		binding,
		_basic_parameters.system_context(),
		this->type(),
		color_format,
		color_format_type,
		internal_color_format,
		sge::renderer::texture::mipmap::level(
			0u
		),
		_parameters.size(),
		fcppt::null_ptr()
	);

	sge::opengl::texture::mipmap::create<
		base_type::dim::dim_wrapper::value
	>(
		sge::opengl::texture::mipmap::parameters<
			base_type::dim::dim_wrapper::value
		>(
			binding,
			_basic_parameters.system_context(),
			this->type(),
			color_format,
			color_format_type,
			internal_color_format,
			_parameters.size(),
			Types::init_function()
		),
		mipmap_
	);

	sge::renderer::texture::mipmap::level_count const mip_levels(
		sge::opengl::texture::mipmap::get_levels<
			base_type::dim::dim_wrapper::value
		>(
			mipmap_,
			_parameters.size()
		)
	);

	typedef sge::opengl::texture::basic_buffer<
		Types
	> gl_buffer;

	for(
		sge::renderer::texture::mipmap::level index(
			0u
		);
		index.get() < mip_levels.get();
		++index
	)
		fcppt::container::ptr::push_back_unique_ptr(
			levels_,
			fcppt::make_unique_ptr<
				gl_buffer
			>(
				fcppt::cref(
					binding
				),
				fcppt::ref(
					_basic_parameters.system_context()
				),
				fcppt::ref(
					_basic_parameters.device_context()
				),
				index,
				this->type(),
				this->id(),
				fcppt::cref(
					_parameters.resource_flags()
				),
				format,
				color_format,
				color_format_type,
				internal_color_format
			)
		);
}

template<
	typename Types
>
sge::opengl::texture::basic<
	Types
>::~basic()
{
}

template<
	typename Types
>
typename sge::opengl::texture::basic<
	Types
>::color_buffer &
sge::opengl::texture::basic<
	Types
>::level(
	sge::renderer::texture::mipmap::level const _level
)
{
	return
		levels_[
			_level.get()
		];
}

template<
	typename Types
>
typename sge::opengl::texture::basic<
	Types
>::color_buffer const &
sge::opengl::texture::basic<
	Types
>::level(
	sge::renderer::texture::mipmap::level const _level
) const
{
	return
		levels_[
			_level.get()
		];
}

template<
	typename Types
>
sge::renderer::texture::mipmap::level_count const
sge::opengl::texture::basic<
	Types
>::levels() const
{
	return
		fcppt::strong_typedef_construct_cast<
			sge::renderer::texture::mipmap::level_count
		>(
			levels_.size()
		);
}

template<
	typename Types
>
sge::renderer::resource_flags_field const
sge::opengl::texture::basic<
	Types
>::resource_flags() const
{
	return resource_flags_;
}

template<
	typename Types
>
sge::renderer::texture::capabilities_field const
sge::opengl::texture::basic<
	Types
>::capabilities() const
{
	return capabilities_;
}

template<
	typename Types
>
sge::renderer::texture::mipmap::object const
sge::opengl::texture::basic<
	Types
>::mipmap() const
{
	return mipmap_;
}

#endif
