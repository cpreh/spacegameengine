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


#ifndef SGE_OPENGL_BASIC_TEXTURE_IMPL_HPP_INCLUDED
#define SGE_OPENGL_BASIC_TEXTURE_IMPL_HPP_INCLUDED

#include "common.hpp"
#include "texfuncs/bind.hpp"
#include "texfuncs/set_filter.hpp"
#include "texfuncs/gen.hpp"
#include "texfuncs/delete.hpp"
#include "convert/color_to_format.hpp"
#include "convert/color_to_format_type.hpp"
#include "create_texture_lock.hpp"
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

template<
	typename Base
>
void
sge::opengl::basic_texture<Base>::bind_me() const
{
	texfuncs::bind(
		type(),
		id()
	);
}

template<
	typename Base
>
void
sge::opengl::basic_texture<Base>::set_my_filter() const
{
	texfuncs::set_filter(
		context_,
		type(),
		filter()
	);
}

template<
	typename Base
>
GLuint
sge::opengl::basic_texture<Base>::id() const
{
	return id_;
}

template<
	typename Base
>
sge::renderer::filter::texture const &
sge::opengl::basic_texture<Base>::filter() const
{
	return filter_;
}

template<
	typename Base
>
void
sge::opengl::basic_texture<Base>::do_lock(
	lock_method::type const method,
	size_type const lock_size,
	size_type const offset,
	size_type const pitch,
	size_type const block_size
) const
{
	check_not_locked();

	scoped_lock_ptr new_lock(
		opengl::create_texture_lock(
			context_,
			method,
			lock_size,
			offset,
			content(),
			stride(),
			pitch,
			block_size,
			flags()
		)
	);

	lock_.swap(
		new_lock
	);
}

template<
	typename Base
>
void
sge::opengl::basic_texture<Base>::post_lock() const
{
	check_locked();

	lock_->post_lock();
}

template<
	typename Base
>
void
sge::opengl::basic_texture<Base>::pre_unlock() const
{
	check_locked();

	lock_->pre_unlock();
}

template<
	typename Base
>
void
sge::opengl::basic_texture<Base>::do_unlock() const
{
	check_locked();

	lock_.reset();
}

template<
	typename Base
>
sge::opengl::lock_method::type
sge::opengl::basic_texture<Base>::lock_mode() const
{
	check_locked();

	return lock_->method();
}

template<
	typename Base
>
typename sge::opengl::basic_texture<Base>::pointer
sge::opengl::basic_texture<Base>::read_buffer() const
{
	check_locked();

	return lock_->read_pointer();
}

template<
	typename Base
>
typename sge::opengl::basic_texture<Base>::pointer
sge::opengl::basic_texture<Base>::write_buffer() const
{
	check_locked();

	return lock_->write_pointer();
}

template<
	typename Base
>
typename sge::opengl::basic_texture<Base>::const_pointer
sge::opengl::basic_texture<Base>::real_read_buffer() const
{
	check_locked();

	return lock_->real_read_pointer();
}

template<
	typename Base
>
typename sge::opengl::basic_texture<Base>::pointer
sge::opengl::basic_texture<Base>::real_write_buffer() const
{
	check_locked();

	return lock_->real_write_pointer();
}

template<
	typename Base
>
void
sge::opengl::basic_texture<Base>::pre_setdata() const
{
	bind_me();
	set_my_filter();
}

template<
	typename Base
>
typename sge::opengl::basic_texture<Base>::size_type
sge::opengl::basic_texture<Base>::stride() const
{
	return stride_;
}

template<
	typename Base
>
GLenum
sge::opengl::basic_texture<Base>::format() const
{
	return format_;
}

template<
	typename Base
>
GLenum
sge::opengl::basic_texture<Base>::format_type() const
{
	return format_type_;
}

template<
	typename Base
>
sge::opengl::basic_texture<Base>::basic_texture(
	opengl::context::object &_context,
	renderer::filter::texture const &_filter,
	renderer::resource_flags_field const &_flags,
	GLenum const _type,
	image::color::format::type const _cformat
)
:
	texture_base(_type),
	context_(_context),
	filter_(_filter),
	flags_(_flags),
	id_(texfuncs::gen()),
	format_(
		convert::color_to_format(
			_cformat
		)
	),
	format_type_(
		convert::color_to_format_type(
			_cformat
		)
	),
	stride_(
		image::color::format_stride(
			_cformat
		)
	)
{}

template<
	typename Base
>
sge::opengl::context::object &
sge::opengl::basic_texture<Base>::context() const
{
	return context_;
}

template<
	typename Base
>
sge::opengl::basic_texture<Base>::~basic_texture()
{
	texfuncs::delete_(id());
}

template<
	typename Base
>
sge::renderer::resource_flags_field const
sge::opengl::basic_texture<Base>::flags() const
{
	return flags_;
}

template<
	typename Base
>
void
sge::opengl::basic_texture<Base>::check_locked() const
{
	if(!lock_)
		throw renderer::exception(
			FCPPT_TEXT("ogl::basic_texture not locked!")
		);
}

template<
	typename Base
>
void
sge::opengl::basic_texture<Base>::check_not_locked() const
{
	if(lock_)
		throw renderer::exception(
			FCPPT_TEXT("ogl::basic_texture already locked!")
		);
}

#endif
