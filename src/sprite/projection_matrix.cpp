/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/projection/orthogonal_viewport.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <sge/sprite/optional_matrix.hpp>
#include <sge/sprite/projection_matrix.hpp>


sge::sprite::optional_matrix const
sge::sprite::projection_matrix(
	sge::renderer::target::viewport const &_viewport
)
{
	return
		sge::renderer::projection::orthogonal_viewport(
			_viewport
		);
}
