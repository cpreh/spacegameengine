/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_OGL_BASIC_ARB_BUFFER_HPP_INCLUDED
#define SGE_OGL_BASIC_ARB_BUFFER_HPP_INCLUDED

#include "common.hpp"
#include "conversion.hpp"
#include "error.hpp"
#include "extension.hpp"

namespace sge
{
namespace ogl
{

template<typename Base, GLenum Type> class basic_arb_buffer : public Base {
public:
	typedef typename Base::value_type value_type;
	typedef typename Base::size_type size_type;
	typedef typename Base::difference_type difference_type;
	typedef typename Base::pointer pointer;
	typedef typename Base::const_pointer const_pointer;
	typedef typename Base::iterator iterator;
	typedef typename Base::const_iterator const_iterator;
	typedef typename Base::reverse_iterator reverse_iterator;
	typedef typename Base::const_reverse_iterator const_reverse_iterator;
			
	basic_arb_buffer(const size_type sz, const size_type _stride, const resource_flag_t _flags, const const_pointer src)
	 : sz(sz), _stride(_stride), _flags(_flags), dest(0)
	{
		glGenBuffersARB(1,&id);
		if(is_error())
			throw std::runtime_error("glGenBuffersARB() failed!");
		_set_size(src);
	}

	~basic_arb_buffer()
	{
		glDeleteBuffersARB(1,&id);
	}

	void lock(const lock_flag_t lockflags)
	{
		if(dest)
			throw std::logic_error("ogl_buffer::lock(), you have to unlock before locking!");
		
		const GLuint glflags = convert_lock_flags(lockflags);
		bind_me();
		dest = static_cast<pointer>(glMapBufferARB(Type,glflags));
		if(is_error())
		{
			dest = 0;
			throw std::runtime_error("glMapBufferARB() failed!");
		}
	}

	void unlock()
	{
		if(!dest)
			throw std::logic_error("ogl_buffer::unlock(), buffer is not locked! cannot unlock!");
		bind_me();
		glUnmapBufferARB(Type);
		dest = 0;

		if(is_error())
			throw std::runtime_error("glUnmapBufferARB() failed!");
	}

	void set_data(const const_pointer data, const size_type first, const size_type count)
	{
		if(first + count > size())
			throw std::length_error("ogl_buffer::set_data(), first + count out of range!");
		if(dest)
			throw std::logic_error("ogl_buffer::set_data(), buffer must not be locked!");
		bind_me();
		glBufferSubDataARB(Type, first * _stride, count * _stride, data);
		if(is_error())
			throw std::runtime_error("glBufferSubDataARB() failed!");
	}

	virtual iterator begin() = 0;
	virtual const_iterator begin() const = 0;
	iterator end() { return begin() + size() * _stride; }
	const_iterator end() const { return begin() + size() * _stride; }
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
	size_type size() const { return sz; }
	resource_flag_t flags() const { return _flags; }
	
	void resize(const size_type newsize, const const_pointer src)
	{
		if(newsize <= size())
			return;
		if(dest)
			throw std::logic_error("ogl_buffer::resize(), buffer must be unlocked!");
		sz = newsize;
		_set_size(src);
	}

	pointer data() { return dest; }
	const_pointer data() const { return dest; }

	void bind_me() const
	{
		glBindBufferARB(Type,id);
		if(is_error())
			throw std::runtime_error("glBindBufferARB() failed!");
	}
private:
	void _set_size(const const_pointer src)
	{
		const GLuint glflags = convert_resource_flags(_flags);
		const size_type nsz = size()*_stride;
		bind_me();
		glBufferDataARB(Type,nsz,src,glflags);
		if(is_error())
			throw std::runtime_error("glBufferDataARB() failed!");
	}
			
	struct init_guard {
		init_guard()
		{
			if(!GLEW_ARB_vertex_buffer_object)
				throw std::runtime_error(extension_not_supported_string("ARB_vertex_buffer_object!"));
		}
	};
	
	init_guard _guard;
	size_type sz;
	size_type _stride;
	resource_flag_t _flags;
	pointer dest;
	GLuint id;
};

}
}

#endif
