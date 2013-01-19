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


#ifndef SGE_CAMERA_SPHERICAL_OBJECT_HPP_INCLUDED
#define SGE_CAMERA_SPHERICAL_OBJECT_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/camera/base.hpp>
#include <sge/camera/has_activation.hpp>
#include <sge/camera/has_mutable_projection.hpp>
#include <sge/camera/is_active.hpp>
#include <sge/camera/is_dynamic.hpp>
#include <sge/camera/optional_projection_matrix.hpp>
#include <sge/camera/symbol.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/spherical/acceleration_factor.hpp>
#include <sge/camera/spherical/damping_factor.hpp>
#include <sge/camera/spherical/maximum_radius.hpp>
#include <sge/camera/spherical/minimum_radius.hpp>
#include <sge/camera/spherical/movement_speed.hpp>
#include <sge/camera/spherical/origin.hpp>
#include <sge/camera/spherical/parameters_fwd.hpp>
#include <sge/camera/spherical/action/mapping.hpp>
#include <sge/camera/spherical/coordinate_system/object.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/mouse/axis_event_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/math/matrix/object_impl.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sge
{
namespace camera
{
namespace spherical
{
class SGE_CLASS_SYMBOL object
:
	public virtual sge::camera::base,
	public sge::camera::has_activation,
	public sge::camera::is_dynamic,
	public sge::camera::has_mutable_projection
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_CAMERA_SYMBOL
	explicit
	object(
		spherical::parameters const &);

	/* override */
	SGE_CAMERA_SYMBOL
	camera::coordinate_system::object const
	coordinate_system() const;

	/* override */
	SGE_CAMERA_SYMBOL
	camera::projection_matrix const
	projection_matrix() const;

	/* override */
	SGE_CAMERA_SYMBOL
	void
	update_projection_matrix(
		sge::camera::projection_matrix const &);

	/* override */
	SGE_CAMERA_SYMBOL
	sge::camera::is_active const
	is_active() const;

	/* override */
	SGE_CAMERA_SYMBOL
	void
	is_active(
		sge::camera::is_active const &);

	/* override */
	SGE_CAMERA_SYMBOL
	void
	update(
		camera::update_duration const &);

	SGE_CAMERA_SYMBOL
	~object();
private:
	fcppt::signal::scoped_connection keyboard_connection_;
	spherical::action::mapping action_mapping_;
	spherical::movement_speed movement_speed_;
	spherical::origin origin_;
	spherical::minimum_radius minimum_radius_;
	spherical::maximum_radius maximum_radius_;
	spherical::acceleration_factor acceleration_factor_;
	spherical::damping_factor damping_factor_;
	sge::camera::is_active is_active_;
	spherical::coordinate_system::object coordinate_system_;
	camera::optional_projection_matrix projection_matrix_;
	spherical::coordinate_system::object acceleration_;
	spherical::coordinate_system::object velocity_;
	bool increase_azimuth_pressed_,decrease_azimuth_pressed_;
	bool increase_inclination_pressed_,decrease_inclination_pressed_;
	bool increase_radius_pressed_,decrease_radius_pressed_;

	void
	key_callback(
		sge::input::keyboard::key_event const &);
};
}
}
}

#endif

