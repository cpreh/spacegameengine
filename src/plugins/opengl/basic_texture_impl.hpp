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


#ifndef SGE_OPENGL_BASIC_TEXTURE_IMPL_HPP_INCLUDED
#define SGE_OPENGL_BASIC_TEXTURE_IMPL_HPP_INCLUDED

#include "common.hpp"
#include "error.hpp"
#include "texture_functions.hpp"
#include "color_convert.hpp"
#include "texture_lock_factory.hpp"
#include <sge/renderer/image_view_format.hpp>
#include <sge/renderer/color_format_stride.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

template<typename Base>
void sge::ogl::basic_texture<Base>::bind_me() const
{
	bind_texture(type(), id());
}

template<typename Base>
void sge::ogl::basic_texture<Base>::set_my_filter() const
{
	set_texture_filter(type(), filter());
}

template<typename Base>
GLuint sge::ogl::basic_texture<Base>::id() const
{
	return id_;
}

template<typename Base>
sge::renderer::filter_args const &
sge::ogl::basic_texture<Base>::filter() const
{
	return filter_;
}

template<typename Base>
void sge::ogl::basic_texture<Base>::do_lock(
	lock_method::type const method,
	size_type const lock_size,
	size_type const offset,
	size_type const pitch) const
{
	check_not_locked();

	scoped_lock_ptr new_lock(
		create_texture_lock(
			method,
			lock_size,
			offset,
			size(),
			stride(),
			pitch,
			flags()));


	lock_.swap(
		new_lock);
}

template<typename Base>
void sge::ogl::basic_texture<Base>::post_lock() const
{
	check_locked();

	lock_->post_lock();
}

template<typename Base>
void sge::ogl::basic_texture<Base>::pre_unlock() const
{
	check_locked();

	lock_->pre_unlock();
}

template<typename Base>
void sge::ogl::basic_texture<Base>::do_unlock() const
{
	check_locked();

	lock_.reset();
}

template<typename Base>
sge::ogl::lock_method::type
sge::ogl::basic_texture<Base>::lock_mode() const
{
	return lock_method_;
}

template<typename Base>
typename sge::ogl::basic_texture<Base>::pointer
sge::ogl::basic_texture<Base>::read_buffer() const
{
	check_locked();

	return lock_->read_pointer();
}

template<typename Base>
typename sge::ogl::basic_texture<Base>::pointer
sge::ogl::basic_texture<Base>::write_buffer() const
{
	check_locked();

	return lock_->write_pointer();
}

template<typename Base>
void sge::ogl::basic_texture<Base>::pre_setdata() const
{
	bind_me();
	set_my_filter();
}

template<typename Base>
typename sge::ogl::basic_texture<Base>::size_type
sge::ogl::basic_texture<Base>::stride() const
{	
	return stride_;
}

template<typename Base>
void sge::ogl::basic_texture<Base>::internal_parameters(
	renderer::const_image_view const &src)
{
	format_internal(
		renderer::image_view_format(
			src));
}

template<typename Base>
void sge::ogl::basic_texture<Base>::format_internal(
	renderer::color_format::type const fmt)
{
	format_ = to_format(fmt);
	format_type_ = to_format_type(fmt);
	stride_ = renderer::color_format_stride(fmt);
}

template<typename Base>
GLenum sge::ogl::basic_texture<Base>::format() const
{	
	return format_;
}

template<typename Base>
GLenum sge::ogl::basic_texture<Base>::format_type() const
{
	return format_type_;
}

template<typename Base>
sge::ogl::basic_texture<Base>::basic_texture(
	const renderer::filter_args& filter_,
	const resource_flag_type flags_,
	const GLenum type_)
 : texture_base(type_),
   filter_(filter_),
   flags_(flags_),
   id_(gen_texture())
{}

template<typename Base>
sge::ogl::basic_texture<Base>::~basic_texture()
{
	delete_texture(id());
}

template<typename Base>
typename sge::ogl::basic_texture<Base>::resource_flag_type
sge::ogl::basic_texture<Base>::flags() const
{
	return flags_;
}

template<typename Base>
void sge::ogl::basic_texture<Base>::check_locked() const
{
	if(!lock_)
		throw exception(
			SGE_TEXT("ogl::basic_texture not locked!"));
}

template<typename Base>
void sge::ogl::basic_texture<Base>::check_not_locked() const
{
	if(lock_)
		throw exception(
			SGE_TEXT("ogl::basic_texture already locked!"));
}

#endif
