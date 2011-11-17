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


#ifndef SGE_CAMERA_PROJECTION_ORTHOGONAL_HPP_INCLUDED
#define SGE_CAMERA_PROJECTION_ORTHOGONAL_HPP_INCLUDED

#include <sge/renderer/projection/rect.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/camera/symbol.hpp>
#include <fcppt/math/box/basic_impl.hpp>

namespace sge
{
namespace camera
{
namespace projection
{
class orthogonal
{
public:
	SGE_CAMERA_SYMBOL explicit
	orthogonal(
		renderer::projection::rect const &,
		renderer::projection::near const &,
		renderer::projection::far const &);

	SGE_CAMERA_SYMBOL renderer::projection::rect const
	rect() const;

	SGE_CAMERA_SYMBOL renderer::scalar
	near() const;

	SGE_CAMERA_SYMBOL renderer::scalar
	far() const;
private:
	renderer::projection::rect rect_;
	renderer::scalar near_;
	renderer::scalar far_;
};
}
}
}

#endif
