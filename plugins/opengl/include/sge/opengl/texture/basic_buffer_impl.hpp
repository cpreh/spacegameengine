//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_BASIC_BUFFER_IMPL_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_BUFFER_IMPL_HPP_INCLUDED

#include <sge/opengl/texture/basic_buffer.hpp>
#include <sge/opengl/texture/basic_buffer_parameters.hpp>
#include <sge/opengl/texture/buffer_base.hpp>
#include <sge/opengl/texture/get_level_size.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/math/dim/static_impl.hpp>


template<
	typename Types
>
sge::opengl::texture::basic_buffer<
	Types
>::basic_buffer(
	format_type const _format,
	const_config_ref,
	sge::opengl::texture::basic_buffer_parameters const &_parameters
)
:
	base_type(),
	sge::opengl::texture::buffer_base(
		_parameters.buffer_type(),
		_parameters.id(),
		_parameters.level(),
		_parameters.is_render_target()
	),
	size_(
		sge::opengl::texture::get_level_size<
			dim::dim_wrapper::value
		>(
			_parameters.binding(),
			_parameters.buffer_type(),
			_parameters.level()
		)
	),
	format_(
		_format
	)
{
}

template<
	typename Types
>
sge::opengl::texture::basic_buffer<
	Types
>::~basic_buffer()
= default;

template<
	typename Types
>
typename
sge::opengl::texture::basic_buffer<
	Types
>::dim
sge::opengl::texture::basic_buffer<
	Types
>::size() const
{
	return
		size_;
}

template<
	typename Types
>
typename
sge::opengl::texture::basic_buffer<
	Types
>::format_type
sge::opengl::texture::basic_buffer<
	Types
>::format() const
{
	return
		format_;
}

#endif
