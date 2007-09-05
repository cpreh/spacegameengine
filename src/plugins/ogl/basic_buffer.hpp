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


#ifndef SGE_OGL_BASIC_BUFFER_HPP_INCLUDED
#define SGE_OGL_BASIC_BUFFER_HPP_INCLUDED

#include "../../exception.hpp"
#include "common.hpp"
#include "conversion.hpp"
#include "error.hpp"

namespace sge
{
namespace ogl
{

template<typename Base, GLenum Type> class basic_buffer : public Base {
public:
	typedef typename Base::value_type value_type;
	typedef typename Base::size_type size_type;
	typedef typename Base::difference_type difference_type;
	typedef typename Base::reference reference;
	typedef typename Base::const_reference const_reference;
	typedef typename Base::pointer pointer;
	typedef typename Base::const_pointer const_pointer;
	typedef typename Base::iterator iterator;
	typedef typename Base::const_iterator const_iterator;
	typedef typename Base::reverse_iterator reverse_iterator;
	typedef typename Base::const_reverse_iterator const_reverse_iterator;
			
	basic_buffer(const size_type sz, const size_type _stride, const resource_flag_t _flags, const const_pointer src)
	 : sz(sz), _stride(_stride), _flags(_flags), dest(0)
	{
		glGenBuffers(1,&id);
		if(is_error())
			throw exception("glGenBuffers() failed!");
		_set_size(src);
	}

	~basic_buffer()
	{
		glDeleteBuffers(1,&id);
	}

	void lock(const lock_flag_t lockflags)
	{
		if(dest)
			throw exception("ogl_buffer::lock(), you have to unlock before locking!");
		
		const GLuint glflags = convert_lock_flags(lockflags);
		bind_me();
		dest = static_cast<pointer>(glMapBuffer(Type,glflags));
		if(is_error())
		{
			dest = 0;
			throw exception("glMapBuffer() failed!");
		}
	}

	void unlock()
	{
		if(!dest)
			throw exception("ogl_buffer::unlock(), buffer is not locked! cannot unlock!");
		bind_me();
		glUnmapBuffer(Type);
		dest = 0;

		if(is_error())
			throw exception("glUnmapBuffer() failed!");
	}

	void set_data(const const_pointer data, const size_type first, const size_type count)
	{
		if(first + count > size())
			throw exception("ogl_buffer::set_data(), first + count out of range!");
		if(dest)
			throw exception("ogl_buffer::set_data(), buffer must not be locked!");
		bind_me();
		glBufferSubData(Type, first * _stride, count * _stride, data);
		if(is_error())
			throw exception("glBufferSubData() failed!");
	}

	void check_lock() const
	{
		if(!dest)
			throw exception("ogl_buffer used but the buffer has not been locked!");
	}

	virtual iterator begin() = 0;
	
	virtual const_iterator begin() const = 0;

	iterator end()
	{
		return begin() + size() * _stride;
	}

	const_iterator end() const
	{
		return begin() + size() * _stride;
	}
	
	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(end());
	}
	
	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}
	
	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(begin());
	}
	
	size_type size() const
	{
		return sz;
	}
	
	resource_flag_t flags() const
	{
		return _flags;
	}

	reference operator[](const size_type i)
	{
		return *(begin() + i);
	}
	
	const_reference operator[](const size_type i) const
	{
		return *(begin() + i);
	}

	void resize(const size_type newsize, const const_pointer src)
	{
		if(newsize <= size())
			return;
		if(dest)
			throw exception("ogl_buffer::resize(), buffer must be unlocked!");
		sz = newsize;
		_set_size(src);
	}

	pointer data()
	{
		check_lock();
		return dest;
	}
	
	const_pointer data() const
	{
		check_lock();
		return dest;
	}

	static void bind(const GLuint id)
	{
		glBindBuffer(Type,id);
		if(is_error())
			throw exception("glBindBuffer() failed!");
	}

	static void unbind()
	{
		bind(0);
	}

	void bind_me() const
	{
		bind(id);
	}
private:
	void _set_size(const const_pointer src)
	{
		const GLuint glflags = convert_resource_flags(_flags);
		const size_type nsz = size()*_stride;
		bind_me();
		glBufferData(Type,nsz,src,glflags);
		if(is_error())
			throw exception("glBufferData() failed!");
	}
			
	size_type sz;
	size_type _stride;
	resource_flag_t _flags;
	pointer dest;
	GLuint id;
};

}
}

#endif
