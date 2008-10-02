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


#ifndef SGE_RENDERER_DEFAULT_TRANSFORMABLE_HPP_INCLUDED
#define SGE_RENDERER_DEFAULT_TRANSFORMABLE_HPP_INCLUDED

#include "transformable.hpp"
#include "device_fwd.hpp"
#include "../export.hpp"
#include "../math/matrix_util.hpp"

namespace sge
{
namespace renderer
{

class SGE_CLASS_SYMBOL default_transformable {
public:
	SGE_SYMBOL default_transformable(
		device_ptr rend,
		math::space_matrix const &internal,
		math::space_matrix const &projecion,
		math::space_matrix const &transform
			= math::matrix_identity());

	SGE_SYMBOL void internal_transformation(
		math::space_matrix const &);
	SGE_SYMBOL void transform(
		math::space_matrix const &);
	SGE_SYMBOL void projection(
		math::space_matrix const &);
	SGE_SYMBOL void set_matrices();
private:
	device_ptr const   rend;
	math::space_matrix internal_matrix_,
			   projection_,
	                   transform_;
};

}
}

#endif
