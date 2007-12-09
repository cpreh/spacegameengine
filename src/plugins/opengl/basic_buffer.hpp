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


#ifndef SGE_OPENGL_BASIC_BUFFER_HPP_INCLUDED
#define SGE_OPENGL_BASIC_BUFFER_HPP_INCLUDED

#include "../../exception.hpp"
#include "../../renderer/types.hpp"
#include "common.hpp"
#include "vbo_common.hpp"

namespace sge
{
namespace ogl
{

template<typename Base, GLenum Type>
class basic_buffer : public Base,
                     private select_vbo_impl<Type>::type {
public:
	typedef typename Base::value_type             value_type;
	typedef typename Base::size_type              size_type;
	typedef typename Base::difference_type        difference_type;
	typedef typename Base::reference              reference;
	typedef typename Base::const_reference        const_reference;
	typedef typename Base::pointer                pointer;
	typedef typename Base::const_pointer          const_pointer;
	typedef typename Base::iterator               iterator;
	typedef typename Base::const_iterator         const_iterator;
	typedef typename Base::reverse_iterator       reverse_iterator;
	typedef typename Base::const_reverse_iterator const_reverse_iterator;
			
	basic_buffer(size_type sz,
	             size_type stride,
	             resource_flag_t flags,
	             const_pointer src);
	~basic_buffer();

	void lock(lock_flag_t lockflags);
	void unlock();
	void set_data(const_pointer data, size_type first, size_type count);

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator rend();
	const_reverse_iterator rend() const;
	
	size_type size() const;
	resource_flag_t flags() const;

	reference operator[](size_type i);
	const_reference operator[](size_type i) const;
	void resize(size_type newsize, const_pointer src);

	pointer data();
	const_pointer data() const;

	static void unbind();
	void bind_me() const;
	
	static pointer buffer_offset(size_type offset);
private:
	typedef typename select_vbo_impl<Type>::type impl;
	using impl::gen_buffer;
	using impl::delete_buffer;
	using impl::bind_buffer;
	using impl::map_buffer;
	using impl::unmap_buffer;
	using impl::buffer_data;
	using impl::buffer_sub_data;

	static void bind(GLuint id);
	void check_lock() const;
	void set_size(const_pointer src);

	virtual iterator create_iterator(pointer) = 0;
	virtual const_iterator create_iterator(const_pointer) const = 0;

	size_type        sz;
	size_type        stride_;
	resource_flag_t  flags_;
	pointer          dest;
	GLuint           id;
};

}
}

#endif
