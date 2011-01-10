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


#include "../index_buffer.hpp"
#include "../common.hpp"
#include "../vbo_context.hpp"
#include "../convert_lock_method.hpp"
#include "../context/use.hpp"
#include <sge/renderer/index/dynamic/make_format.hpp>
#include <sge/renderer/index/view.hpp>
#include <sge/renderer/index/i16.hpp>
#include <sge/renderer/index/i32.hpp>
#include <sge/renderer/index/format.hpp>
#include <fcppt/variant/object_impl.hpp>

namespace
{

template<
	typename T
>
struct gl_format_c;

template<>
struct gl_format_c<
	sge::renderer::index::i16
>
{
	static GLenum const value = GL_UNSIGNED_SHORT;
};

template<>
struct gl_format_c<
	sge::renderer::index::i32
>
{
	static GLenum const value = GL_UNSIGNED_INT;
};

}

template<
	typename T
>
sge::opengl::index_buffer<T>::index_buffer(
	context::object &_context,
	size_type const _size,
	renderer::resource_flags_field const &_flags
)
:
	buf(
		context::use<
			vbo_context
		>(
			_context
		).impl(),
		context::use<
			vbo_context
		>(
			_context
		).index_buffer_type(),
		_size,
		sizeof(T),
		_flags,
		0
	)
{}

template<
	typename T
>
GLenum
sge::opengl::index_buffer<T>::gl_format() const
{
	return
		::gl_format_c<
			T
		>::value;
}

template<
	typename T
>
void *
sge::opengl::index_buffer<T>::buffer_offset(
	size_type const sz) const
{
	return buf.buffer_offset(
		sz
	);
}

template<
	typename T
>
void
sge::opengl::index_buffer<T>::bind_me() const
{
	buf.bind_me();
}

// FIXME: fix the reinterpret_casts!

template<
	typename T
>
typename sge::opengl::index_buffer<T>::view_type const
sge::opengl::index_buffer<T>::lock(
	renderer::lock_mode::type const _flags,
	size_type const _offset,
	size_type const _range
)
{
	buf.lock(
		opengl::convert_lock_method(
			_flags
		),
		_offset,
		_range
	);

	return 
		view_type(
			renderer::index::view<
				sge::renderer::index::format<
					T
				>
			>(
				reinterpret_cast<
					T *
				>(
					buf.data()
				),
				buf.lock_size() / sizeof(T) // FIXME
			)
		);
}

template<
	typename T
>
typename sge::opengl::index_buffer<T>::const_view_type const
sge::opengl::index_buffer<T>::lock(
	size_type const _offset,
	size_type const _range
) const
{
	buf.lock(
		lock_method::readonly,
		_offset,
		_range
	);

	return 
		const_view_type(
			renderer::index::view<
				sge::renderer::index::format<
					T const
				>
			>(
				reinterpret_cast<
					T const *
				>(
					buf.data()
				),
				buf.lock_size() / sizeof(T) // FIXME
			)
		);
}

template<
	typename T
>
void
sge::opengl::index_buffer<T>::unlock() const
{
	buf.unlock();
}

template<
	typename T
>
typename sge::opengl::index_buffer<T>::size_type
sge::opengl::index_buffer<T>::size() const
{
	return buf.size();
}

template<
	typename T
>
sge::renderer::resource_flags_field const
sge::opengl::index_buffer<T>::flags() const
{
	return buf.flags();
}

template<
	typename T
>
sge::renderer::index::dynamic::format::type
sge::opengl::index_buffer<T>::format() const
{
	return
		renderer::index::dynamic::make_format<
			sge::renderer::index::format<
				T
			>
		>();
}

#define SGE_OPENGL_INSTANTIATE_INDEX_BUFFER(t) \
template class sge::opengl::index_buffer<t>;

SGE_OPENGL_INSTANTIATE_INDEX_BUFFER(
	sge::renderer::index::i16
)
SGE_OPENGL_INSTANTIATE_INDEX_BUFFER(
	sge::renderer::index::i32
)

#undef SGE_OPENGL_INSTANTIATE_INDEX_BUFFER
