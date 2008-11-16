/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
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


#ifndef SGE_OPENGL_BASIC_TEXTURE_HPP_INCLUDED
#define SGE_OPENGL_BASIC_TEXTURE_HPP_INCLUDED

#include "common.hpp"
#include "texture_lock.hpp"
#include "texture_base.hpp"
#include "lock_method.hpp"
#include <sge/renderer/texture_filter.hpp>
#include <sge/renderer/image_view.hpp>
#include <sge/renderer/color_format.hpp>
#include <boost/scoped_ptr.hpp>

namespace sge
{
namespace ogl
{

template<typename Base>
class basic_texture : public Base, public texture_base {
public:
	typedef typename Base::size_type size_type;
	typedef texture_lock::pointer pointer;
	typedef texture_lock::const_pointer const_pointer;
	typedef typename Base::resource_flag_type resource_flag_type;
	typedef typename Base::lock_flag_type lock_flag_type;
protected:
	void bind_me() const;
	void set_my_filter() const;
	GLuint id() const;
	renderer::texture_filter const& filter() const;
	
	void do_lock(
		lock_method::type mode,
		size_type size,
		size_type offset,
		size_type pitch,
		size_type block_size) const;

	void post_lock() const;
	void pre_unlock() const;
	void do_unlock() const;
	lock_method::type lock_mode() const;
	pointer read_buffer() const;
	pointer write_buffer() const;
	const_pointer real_read_buffer() const;
	pointer real_write_buffer() const;
	
	void pre_setdata() const;
	
	using Base::content;

public:
	size_type stride() const;

	GLenum format() const;
	GLenum format_type() const;
protected:
	basic_texture(
		renderer::texture_filter const &filter,
		resource_flag_type flags,
		GLenum type,
		renderer::color_format::type);
public:
	~basic_texture();
	resource_flag_type flags() const;
private:
	void check_locked() const;
	void check_not_locked() const;

	renderer::texture_filter const            filter_;
	resource_flag_type const               flags_;
	GLuint const                           id_;

	GLenum const                           format_,
	                                       format_type_;
	size_type const                        stride_;

	typedef boost::scoped_ptr<
		texture_lock>                  scoped_lock_ptr;
	mutable scoped_lock_ptr                lock_;
};

}
}

#endif

