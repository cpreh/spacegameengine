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


#include <sge/renderer/projection/perspective_af.hpp>
#include <sge/renderer/projection/dim.hpp>
#include <sge/renderer/projection/perspective_wh.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <cmath>

sge::renderer::matrix4 const
sge::renderer::projection::perspective_af(
	projection::aspect const _aspect,
	projection::fov const _fov,
	projection::near const _near,
	projection::far const _far
)
{
	renderer::scalar const
		h(
			1.f
			/
			std::tan(
				_fov.get()
				/
				2.f
			)
		),
		w(
			h
			/
			_aspect.get()
		);

	return
		projection::perspective_wh(
			projection::dim(
				w,
				h
			),
			_near,
			_far
		);
}
