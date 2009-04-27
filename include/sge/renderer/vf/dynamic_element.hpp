/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#ifndef SGE_RENDERER_VF_DYNAMIC_ELEMENT_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_ELEMENT_HPP_INCLUDED

#include <sge/renderer/vf/dynamic_any.hpp>
#include <sge/renderer/vf/role.hpp>
#include <sge/renderer/vf/vertex_size.hpp>
#include <sge/variant/object_impl.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace renderer
{
namespace vf
{

class dynamic_element {
public:
	SGE_SYMBOL dynamic_element(
		dynamic_any const &,
		vf::role::type,
		vertex_size index);
	
	SGE_SYMBOL dynamic_any const &info() const;
	SGE_SYMBOL vf::role::type role() const;
	SGE_SYMBOL vertex_size index() const;
private:
	dynamic_any    info_;
	vf::role::type role_;
	vertex_size    index_;
};

}
}
}

#endif
