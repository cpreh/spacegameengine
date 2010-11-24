/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/camera/projection/perspective.hpp>

sge::camera::projection::perspective::perspective(
	renderer::scalar const _aspect,
	renderer::scalar const _fov,
	renderer::scalar const _near,
	renderer::scalar const _far)
:
	aspect_(
		_aspect),
	fov_(
		_fov),
	near_(
		_near),
	far_(
		_far)
{
}

sge::renderer::scalar 
sge::camera::projection::perspective::aspect() const
{
	return aspect_;
}

sge::renderer::scalar 
sge::camera::projection::perspective::fov() const
{
	return fov_;
}

sge::renderer::scalar 
sge::camera::projection::perspective::near() const
{
	return near_;
}

sge::renderer::scalar 
sge::camera::projection::perspective::far() const
{
	return far_;
}
