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


#ifndef SGE_CAMERA_ORTHO_FREELOOK_OBJECT_HPP_INCLUDED
#define SGE_CAMERA_ORTHO_FREELOOK_OBJECT_HPP_INCLUDED

#include <sge/camera/base.hpp>
#include <sge/camera/ortho_freelook/parameters_fwd.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/mouse/axis_event_fwd.hpp>
#include <sge/renderer/vector2.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sge
{
namespace camera
{
namespace ortho_freelook
{
class SGE_CLASS_SYMBOL object
:
	public camera::base
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_CAMERA_SYMBOL
	explicit
	object(
		ortho_freelook::parameters const &);

	SGE_CAMERA_SYMBOL
	void
	update(
		camera::duration const &);

	SGE_CAMERA_SYMBOL
	bool
	active() const;

	SGE_CAMERA_SYMBOL
	void
	active(
		bool);

	SGE_CAMERA_SYMBOL
	~object();
private:
	fcppt::signal::scoped_connection mouse_axis_connection_;
	fcppt::signal::scoped_connection keyboard_key_connection_;
	renderer::vector2 zoom_to_panning_speed_factor_;
	renderer::vector2 zoom_to_zooming_speed_factor_;
	bool zoom_in_;
	bool zoom_out_;
	bool active_;

	void
	mouse_axis_callback(
		input::mouse::axis_event const &);

	void
	keyboard_key_callback(
		input::keyboard::key_event const &);
};
}
}
}

#endif
