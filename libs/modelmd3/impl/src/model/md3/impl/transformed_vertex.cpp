/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/model/md3/impl/convert_normal.hpp>
#include <sge/model/md3/impl/transformed_vertex.hpp>
#include <sge/model/md3/impl/vec3.hpp>
#include <sge/model/md3/impl/vertex.hpp>
#include <sge/model/md3/impl/xyz_scale.hpp>
#include <fcppt/cast/int_to_float.hpp>


sge::model::md3::impl::transformed_vertex::transformed_vertex(
	sge::model::md3::impl::vertex const &_vertex
)
:
	pos_(
		// TODO: Don't do this element-wise
		fcppt::cast::int_to_float<
			sge::model::md3::scalar
		>(
			_vertex.x()
		)
		*
		sge::model::md3::impl::xyz_scale()
		,
		fcppt::cast::int_to_float<
			sge::model::md3::scalar
		>(
			_vertex.y()
		)
		*
		sge::model::md3::impl::xyz_scale()
		,
		fcppt::cast::int_to_float<
			sge::model::md3::scalar
		>(
			_vertex.z()
		)
		*
		sge::model::md3::impl::xyz_scale()
	),
	normal_(
		sge::model::md3::impl::convert_normal(
			_vertex.normal()
		)
	)
{
}

sge::model::md3::impl::vec3 const &
sge::model::md3::impl::transformed_vertex::pos() const
{
	return
		pos_;
}

sge::model::md3::impl::vec3 const &
sge::model::md3::impl::transformed_vertex::normal() const
{
	return
		normal_;
}
