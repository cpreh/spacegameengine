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


#ifndef SGE_CAMERA_OBJECT_HPP_INCLUDED
#define SGE_CAMERA_OBJECT_HPP_INCLUDED

#include <sge/camera/parameters_fwd.hpp>
#include <sge/camera/projection/object.hpp>
#include <sge/camera/gizmo_type.hpp>
#include <sge/camera/symbol.hpp>
#include <sge/renderer/matrix4.hpp>
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
/// The camera is a class which holds a gizmo (the camera position and
/// orientation) and manipulates it via keyboard and mouse input. It
/// also offers all of the transformation matrices to be used in the
/// shaders, including the perspective matrix (the other ones you
/// could derive from the gizmo).
class object
{
	FCPPT_NONCOPYABLE(
		object
	)
public:
	SGE_CAMERA_SYMBOL
	explicit
	object(
		parameters const &);
	
	SGE_CAMERA_SYMBOL
	~object();
	
	SGE_CAMERA_SYMBOL
	void
	update(
		renderer::scalar);
	
	SGE_CAMERA_SYMBOL
	renderer::matrix4 const
	world() const;

	SGE_CAMERA_SYMBOL
	renderer::matrix4 const
	rotation() const;

	SGE_CAMERA_SYMBOL
	renderer::matrix4 const
	translation() const;

	SGE_CAMERA_SYMBOL
	renderer::matrix4 const
	projection() const;

	SGE_CAMERA_SYMBOL
	renderer::matrix4 const 
	mvp() const;

	SGE_CAMERA_SYMBOL
	gizmo_type const &
	gizmo() const;

	SGE_CAMERA_SYMBOL
	gizmo_type &
	gizmo();
private:
	fcppt::signal::scoped_connection keyboard_connection_,mouse_axis_connection_;
	projection::object const projection_;
	renderer::matrix4 const projection_matrix_;
	// Rotation speed means mouse sensitivity, movement-speed should be
	// self-explanatory
	renderer::scalar const movement_speed_,rotation_speed_;
	// The camera's position and orientation
	gizmo_type gizmo_;
	// Those are the directions the camera currently moves in
	// (corresponds to the movement keys currently pressed)
	renderer::vector3 dirs_;

	void
	key_callback(
		sge::input::keyboard::key_event const &);

	void
	mouse_axis_callback(
		sge::input::mouse::axis_event const &);
};
}
}

#endif
