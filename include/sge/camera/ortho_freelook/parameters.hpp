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


#ifndef SGE_CAMERA_ORTHO_FREELOOK_PARAMETERS_HPP_INCLUDED
#define SGE_CAMERA_ORTHO_FREELOOK_PARAMETERS_HPP_INCLUDED

#include <sge/camera/symbol.hpp>
#include <sge/camera/projection/object.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/mouse/device_fwd.hpp>
#include <sge/renderer/vector2.hpp>
#include <sge/renderer/projection/rect.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/variant/object_impl.hpp>


namespace sge
{
namespace camera
{
namespace ortho_freelook
{
class parameters
{
FCPPT_NONASSIGNABLE(
	parameters);
public:
	SGE_CAMERA_SYMBOL explicit
	parameters(
		input::mouse::device &,
		input::keyboard::device &,
		renderer::projection::rect const &);

	SGE_CAMERA_SYMBOL input::mouse::device &
	mouse() const;

	SGE_CAMERA_SYMBOL input::keyboard::device &
	keyboard() const;

	SGE_CAMERA_SYMBOL camera::projection::object const
	projection() const;

	SGE_CAMERA_SYMBOL parameters &
	near(
		renderer::scalar);

	SGE_CAMERA_SYMBOL parameters &
	far(
		renderer::scalar);

	SGE_CAMERA_SYMBOL parameters &
	zoom_to_zooming_speed_factor(
		renderer::vector2 const &);

	SGE_CAMERA_SYMBOL parameters &
	zoom_to_panning_speed_factor(
		renderer::vector2 const &);

	SGE_CAMERA_SYMBOL parameters &
	active(
		bool);

	SGE_CAMERA_SYMBOL renderer::scalar
	near() const;

	SGE_CAMERA_SYMBOL renderer::scalar
	far() const;

	SGE_CAMERA_SYMBOL renderer::vector2 const &
	zoom_to_zooming_speed_factor() const;

	SGE_CAMERA_SYMBOL renderer::vector2 const &
	zoom_to_panning_speed_factor() const;

	SGE_CAMERA_SYMBOL bool
	active() const;
private:
	input::mouse::device &mouse_;
	input::keyboard::device &keyboard_;
	renderer::projection::rect const rect_;
	renderer::scalar near_;
	renderer::scalar far_;
	renderer::vector2 zoom_to_zooming_speed_factor_;
	renderer::vector2 zoom_to_panning_speed_factor_;
	bool active_;
};
}
}
}

#endif
