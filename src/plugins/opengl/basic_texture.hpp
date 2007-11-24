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

#include <boost/scoped_ptr.hpp>
#include "common.hpp"
#include "pbo.hpp"
#include "texture_base.hpp"

namespace sge
{
namespace ogl
{

template<typename Base, GLenum Type> class basic_texture : public Base, public texture_base {
private:
	void check_lock() const;
protected:
	void bind_me() const;
	void set_my_filter() const;
	GLuint id() const;
	const filter_args& filter() const;
	void do_lock(lock_flag_t flags);
	void post_lock();
	void pre_unlock();
	void do_unlock();
	lock_flag_t lock_mode() const;
	void pre_setdata() const;
public:
	typedef typename Base::value_type value_type;
	typedef typename Base::size_type size_type;
	typedef typename Base::difference_type difference_type;
	typedef typename Base::pointer pointer;
	typedef typename Base::const_pointer const_pointer;

	basic_texture(const filter_args& filter, resource_flag_t flags);
	~basic_texture();
	virtual size_type size() const = 0;
	resource_flag_t flags() const;
	pointer data();
	const_pointer data() const;
private:
	filter_args                            filter_;
	resource_flag_t                        flags_;
	GLuint                                 id_;
	pbo_base*                              cur_buffer;
	lock_flag_t                            lock_mode_;
	boost::scoped_ptr<pixel_pack_buffer>   pack_buffer;
	boost::scoped_ptr<pixel_unpack_buffer> unpack_buffer;
};

}
}

#endif

