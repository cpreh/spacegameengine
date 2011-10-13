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


#ifndef SGE_CAMERA_SPHERICAL_OBJECT_HPP_INCLUDED
#define SGE_CAMERA_SPHERICAL_OBJECT_HPP_INCLUDED

#include <sge/camera/base.hpp>
#include <sge/camera/duration.hpp>
#include <sge/camera/spherical/movement_speed.hpp>
#include <sge/camera/spherical/object_fwd.hpp>
#include <sge/camera/spherical/parameters_fwd.hpp>
#include <sge/camera/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/vector2.hpp>
#include <sge/renderer/vector3.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/mouse/axis_event_fwd.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace camera
{
namespace spherical
{

class SGE_CLASS_SYMBOL object
:
	public camera::base
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	SGE_CAMERA_SYMBOL
	explicit
	object(
		spherical::parameters const &);

	SGE_CAMERA_SYMBOL
	~object();

	SGE_CAMERA_SYMBOL
	void
	update(
		camera::duration const &);

	SGE_CAMERA_SYMBOL
	void
	active(
		bool);

	SGE_CAMERA_SYMBOL
	bool
	active() const;
private:
	fcppt::signal::scoped_connection keyboard_connection_;
	sge::renderer::scalar const movement_speed_;
	sge::renderer::scalar const min_radius_;
	sge::renderer::scalar const acceleration_factor_;
	sge::renderer::scalar const damping_;
	sge::renderer::vector3 dirs_;
	sge::renderer::vector3 acc_;
	sge::renderer::scalar radius_;
	// radius, elevation theta in [-pi,pi], azimuth phi in [0,2pi)
	sge::renderer::vector2 angles_;
	bool active_;

	void
	key_callback(
		input::keyboard::key_event const &);
};
}
}
}

#endif
