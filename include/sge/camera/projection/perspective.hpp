/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_CAMERA_PROJECTION_PERSPECTIVE_HPP_INCLUDED
#define SGE_CAMERA_PROJECTION_PERSPECTIVE_HPP_INCLUDED

#include <sge/camera/symbol.hpp>
#include <sge/renderer/projection/aspect.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/fov.hpp>
#include <sge/renderer/projection/near.hpp>

namespace sge
{
namespace camera
{
namespace projection
{
class perspective
{
public:
	SGE_CAMERA_SYMBOL
	explicit
	perspective(
		renderer::projection::aspect,
		renderer::projection::fov,
		renderer::projection::near,
		renderer::projection::far);

	SGE_CAMERA_SYMBOL
	renderer::projection::aspect const
	aspect() const;

	SGE_CAMERA_SYMBOL
	renderer::projection::fov const
	fov() const;

	SGE_CAMERA_SYMBOL
	renderer::projection::near const
	near() const;

	SGE_CAMERA_SYMBOL
	renderer::projection::far const
	far() const;
private:
	renderer::projection::aspect aspect_;
	renderer::projection::fov fov_;
	renderer::projection::near near_;
	renderer::projection::far far_;
};
}
}
}

#endif
