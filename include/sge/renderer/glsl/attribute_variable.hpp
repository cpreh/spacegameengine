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


#ifndef SGE_RENDERER_GLSL_ATTRIBUTE_VARIABLE_HPP_INCLUDED
#define SGE_RENDERER_GLSL_ATTRIBUTE_VARIABLE_HPP_INCLUDED

#include "../../su.hpp"
#include "../../shared_ptr.hpp"
#include "../../math/vector.hpp"
#include <boost/noncopyable.hpp>

namespace sge
{
namespace renderer
{
namespace glsl
{

class attribute_variable : boost::noncopyable {
public:
	virtual void set(space_unit) = 0;
	virtual void set(const math::vector2&) = 0;
	virtual void set(const math::vector3&) = 0;
	virtual void set(const math::vector4&) = 0;

	virtual ~attribute_variable() {}
};

typedef shared_ptr<attribute_variable> attribute_variable_ptr;

}
}
}

#endif
