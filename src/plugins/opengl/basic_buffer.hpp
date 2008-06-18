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

#include "common.hpp"
#include <sge/renderer/types.hpp>

namespace sge
{
namespace ogl
{

class vbo_base;

template<typename Base>
class basic_buffer : public Base {
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
	typedef typename Base::resource_flag_type     resource_flag_type;
	typedef typename Base::lock_flag_type         lock_flag_type;
			
	basic_buffer(
		GLenum type,
		vbo_base&,
		size_type sz,
		size_type stride,
		resource_flag_type flags,
		const_pointer src);
	~basic_buffer();

	void lock(lock_flag_type lockflags);
	void unlock();
	void set_data(const_pointer data, size_type first, size_type count);

	size_type size() const;
	resource_flag_type flags() const;

	void resize(size_type newsize, const_pointer src);

	iterator begin();
	const_iterator begin() const;
	pointer data();
	const_pointer data() const;

	void unbind() const;
	void bind_me() const;
	
	pointer buffer_offset(size_type offset) const;
private:
	void bind(GLuint id) const;
	void check_lock() const;
	void set_size(const_pointer src);

	virtual iterator create_iterator(pointer) = 0;
	virtual const_iterator create_iterator(const_pointer) const = 0;
	
	GLenum             type;
	vbo_base&          impl;
	size_type          sz;
	size_type          stride_;
	resource_flag_type flags_;
	pointer            dest;
	GLuint             id;
};

}
}

#endif
