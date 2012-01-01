/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_GLSL_UNIFORM_VARIABLE_HPP_INCLUDED
#define SGE_RENDERER_GLSL_UNIFORM_VARIABLE_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/glsl/uniform/value.hpp>
#include <sge/renderer/glsl/uniform/variable_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace glsl
{
namespace uniform
{

/**
\brief A dynamic representation of a uniform variable

This class is a dynamic representation of a uniform variable and is retrieved
from a glsl::program. It can be used to set or get a uniform value from GLSL.

\see uniform::value
\see glsl::program
*/
class SGE_CLASS_SYMBOL variable
{
	FCPPT_NONCOPYABLE(
		variable
	);
protected:
	SGE_RENDERER_SYMBOL
	variable();
public:
	/**
	\brief Get the uniform value

	\return A copy of the uniform value
	*/
	virtual uniform::value const
	get() const = 0;

	/**
	\brief Set the uniform value

	Sets the uniform value to \a value
	*/
	virtual void
	set(
		uniform::value const &value
	) = 0;

	SGE_RENDERER_SYMBOL
	virtual ~variable() = 0;
};

}
}
}
}

#endif
