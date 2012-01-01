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


#ifndef SGE_RENDERER_GLSL_UNIFORM_VARIABLE_PTR_HPP_INCLUDED
#define SGE_RENDERER_GLSL_UNIFORM_VARIABLE_PTR_HPP_INCLUDED

#include <sge/renderer/glsl/uniform/variable_fwd.hpp>
#include <fcppt/shared_ptr_impl.hpp>


namespace sge
{
namespace renderer
{
namespace glsl
{
namespace uniform
{

/**
 * \brief A shared pointer to a uniform::variable
*/
typedef fcppt::shared_ptr<
	uniform::variable
> variable_ptr;

}
}
}
}

#endif
