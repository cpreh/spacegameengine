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


#ifndef SGE_CAMERA_SPHERICAL_PARAMETERS_HPP_INCLUDED
#define SGE_CAMERA_SPHERICAL_PARAMETERS_HPP_INCLUDED

#include <sge/camera/gizmo_type.hpp>
#include <sge/camera/projection/object.hpp>
#include <sge/camera/spherical/movement_speed.hpp>
#include <sge/camera/spherical/parameters_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/renderer/scalar.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace camera
{
namespace spherical
{
class parameters
{
FCPPT_NONASSIGNABLE(
	parameters);
public:
	SGE_CAMERA_SYMBOL explicit
	parameters(
		sge::camera::spherical::movement_speed const &,
		sge::renderer::scalar const,
		sge::input::keyboard::device &);

	SGE_CAMERA_SYMBOL spherical::parameters &
	projection(
		sge::camera::projection::object const &);

	SGE_CAMERA_SYMBOL spherical::parameters &
	gizmo(
		sge::camera::gizmo_type const &);

	SGE_CAMERA_SYMBOL spherical::parameters &
	active(
		bool);

	SGE_CAMERA_SYMBOL spherical::parameters &
	radius(
		sge::renderer::scalar);

	SGE_CAMERA_SYMBOL spherical::parameters &
	acceleration_factor(
		sge::renderer::scalar);

	SGE_CAMERA_SYMBOL spherical::parameters &
	damping(
		sge::renderer::scalar);

	SGE_CAMERA_SYMBOL
	sge::camera::projection::object const &
	projection() const;

	SGE_CAMERA_SYMBOL
	sge::renderer::scalar
	movement_speed() const;

	SGE_CAMERA_SYMBOL
	sge::renderer::scalar
	min_radius() const;

	SGE_CAMERA_SYMBOL
	sge::renderer::scalar
	radius() const;

	SGE_CAMERA_SYMBOL
	sge::renderer::scalar
	acceleration_factor() const;

	SGE_CAMERA_SYMBOL
	sge::renderer::scalar
	damping() const;

	SGE_CAMERA_SYMBOL
	sge::camera::gizmo_type const &
	gizmo() const;

	SGE_CAMERA_SYMBOL
	sge::input::keyboard::device &
	keyboard() const;

	bool
	active() const;
private:
	sge::camera::projection::object projection_;
	sge::renderer::scalar const movement_speed_;
	sge::renderer::scalar const min_radius_;
	sge::renderer::scalar acceleration_factor_;
	sge::renderer::scalar damping_;
	sge::renderer::scalar radius_;
	sge::camera::gizmo_type gizmo_;
	sge::input::keyboard::device &keyboard_;
	bool active_;
};
}
}
}

#endif
