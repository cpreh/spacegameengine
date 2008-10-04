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


#ifndef SGE_RENDERER_VF_DYNAMIC_VIEW_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_VIEW_HPP_INCLUDED

#include "vertex_size.hpp"
#include "raw_pointer.hpp"
#include "../../export.hpp"

namespace sge
{
namespace renderer
{
namespace vf
{

class dynamic_format;

template<typename Pointer>
class basic_dynamic_view {
public:
	typedef Pointer     pointer;
	typedef vertex_size size_type;

	SGE_SYMBOL basic_dynamic_view(
		pointer data,
		size_type elements,
		dynamic_format const &);
	
	SGE_SYMBOL pointer data() const;
	SGE_SYMBOL size_type size() const;
	SGE_SYMBOL dynamic_format const &format() const;
private:
	pointer        const data_;
	size_type      const size_;
	dynamic_format const &format_;
};

typedef basic_dynamic_view<raw_pointer> dynamic_view;
typedef basic_dynamic_view<const_raw_pointer> const_dynamic_view;

}
}
}

#endif
