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


#include <sge/model/md3/scalar.hpp>
#include <sge/src/model/md3/convert_normal.hpp>
#include <sge/src/model/md3/transformed_vertex.hpp>
#include <sge/src/model/md3/vec3.hpp>
#include <sge/src/model/md3/vertex.hpp>
#include <sge/src/model/md3/xyz_scale.hpp>


sge::model::md3::transformed_vertex::transformed_vertex(
	md3::vertex const &_vertex
)
:
	pos_(
		static_cast<
			md3::scalar
		>(
			_vertex.x()
		)
		* md3::xyz_scale()
		,
		static_cast<
			md3::scalar
		>(
			_vertex.y()
		)
		* md3::xyz_scale()
		,
		static_cast<
			md3::scalar
		>(
			_vertex.z()
		)
		*
		md3::xyz_scale()
	),
	normal_(
		md3::convert_normal(
			_vertex.normal()
		)
	)
{
}

sge::model::md3::vec3 const &
sge::model::md3::transformed_vertex::pos() const
{
	return pos_;
}

sge::model::md3::vec3 const &
sge::model::md3::transformed_vertex::normal() const
{
	return normal_;
}
