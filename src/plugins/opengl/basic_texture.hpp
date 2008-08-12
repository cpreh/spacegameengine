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


#ifndef SGE_OPENGL_BASIC_TEXTURE_HPP_INCLUDED
#define SGE_OPENGL_BASIC_TEXTURE_HPP_INCLUDED

#include "common.hpp"
#include "pixel_pack_buffer.hpp"
#include "pixel_unpack_buffer.hpp"
#include "texture_base.hpp"
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
	void check_lock() const;
public:
	typedef typename Base::size_type size_type;
	typedef typename Base::difference_type difference_type;
	typedef pixel_pack_buffer::pointer pointer;
	typedef pixel_pack_buffer::const_pointer const_pointer;
	typedef typename Base::resource_flag_type resource_flag_type;
	typedef typename Base::lock_flag_type lock_flag_type;
protected:
	void bind_me() const;
	void set_my_filter() const;
	GLuint id() const;
	renderer::filter_args const& filter() const;
	
	void do_lock(
		lock_flag_type flags,
		size_type size,
		size_type offset);
	void post_lock();
	void pre_unlock();
	void do_unlock();
	lock_flag_type lock_mode() const;
	pointer read_buffer() const;
	pointer write_buffer() const;
	
	void pre_setdata() const;
	
	using Base::content;
	size_type stride() const;

	void internal_parameters(
		renderer::const_image_view const &src);
	void format_internal(
		renderer::color_format::type);
	GLenum format() const;
	GLenum format_type() const;

	basic_texture(
		const renderer::filter_args& filter,
		resource_flag_type flags,
		GLenum type);
public:
	~basic_texture();
	resource_flag_type flags() const;
	pointer raw_data();
	const_pointer raw_data() const;
private:
	renderer::filter_args                  filter_;
	resource_flag_type                     flags_;
	GLuint                                 id_;
	pbo_base*                              cur_buffer;

	GLenum                                 format_,
	                                       format_type_;
	size_type                              stride_,
	                                       lock_offset_;
	lock_flag_type                         lock_mode_;
	boost::scoped_ptr<pixel_pack_buffer>   pack_buffer;
	boost::scoped_ptr<pixel_unpack_buffer> unpack_buffer;
};

}
}

#endif

