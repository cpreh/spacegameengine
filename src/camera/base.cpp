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


#include <sge/camera/base.hpp>
#include <sge/camera/gizmo/to_rotation_matrix.hpp>
#include <sge/camera/projection/to_matrix.hpp>
#include <fcppt/math/matrix/translation.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

sge::camera::base::base(
	camera::projection::object const &_projection_object,
	camera::gizmo_type const &_gizmo)
:
	projection_object_(
		_projection_object),
	projection_matrix_(
		projection::to_matrix(
			projection_object_)),
	gizmo_(
		_gizmo)
{

}

sge::renderer::matrix4 const
sge::camera::base::world() const
{
	return
		this->rotation() *
		this->translation();
}

sge::renderer::matrix4 const
sge::camera::base::rotation() const
{
	return
		gizmo::to_rotation_matrix(
			gizmo_);
}

sge::renderer::matrix4 const
sge::camera::base::translation() const
{
	return
		fcppt::math::matrix::translation(
			-gizmo_.position());
}

sge::renderer::matrix4 const
sge::camera::base::projection() const
{
	return projection_matrix_;
}

sge::camera::projection::object const
sge::camera::base::projection_object() const
{
	return projection_object_;
}

void
sge::camera::base::projection_object(
	projection::object const &_projection_object)
{
	projection_object_ =
		_projection_object;
	projection_matrix_ =
		projection::to_matrix(
			projection_object_);
}


sge::renderer::matrix4 const
sge::camera::base::mvp() const
{
	return
		this->projection() * this->world();
}

sge::camera::gizmo_type const &
sge::camera::base::gizmo() const
{
	return gizmo_;
}

sge::camera::gizmo_type &
sge::camera::base::gizmo()
{
	return gizmo_;
}

sge::camera::base::~base()
{
}
