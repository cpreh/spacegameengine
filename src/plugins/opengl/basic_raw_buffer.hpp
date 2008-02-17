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


#ifndef SGE_OPENGL_BASIC_RAW_BUFFER_HPP_INCLUDED
#define SGE_OPENGL_BASIC_RAW_BUFFER_HPP_INCLUDED

#include "../../renderer/types.hpp"
#include "basic_buffer.hpp"
#include "common.hpp"

namespace sge
{
namespace ogl
{

class vbo_base;

template<
	typename Base,
	GLenum (*Type)(),
	vbo_base& (*Impl)()>
class basic_raw_buffer : public basic_buffer<Base> {
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

	basic_raw_buffer(
		size_type,
		resource_flag_t,
		const_pointer src);

	typedef basic_buffer<Base> base_type;
	using base_type::buffer_offset;
private:
	iterator create_iterator(pointer);
	const_iterator create_iterator(const_pointer) const;
};

}
}

#endif
