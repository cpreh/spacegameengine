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


#ifndef SGE_CAMERA_ORTHO_FREELOOK_PARAMETERS_HPP_INCLUDED
#define SGE_CAMERA_ORTHO_FREELOOK_PARAMETERS_HPP_INCLUDED

#include <sge/camera/is_active.hpp>
#include <sge/camera/symbol.hpp>
#include <sge/camera/ortho_freelook/optional_projection_rectangle.hpp>
#include <sge/camera/ortho_freelook/pan_speed.hpp>
#include <sge/camera/ortho_freelook/zoom_speed.hpp>
#include <sge/camera/ortho_freelook/action/mapping.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/mouse/device_fwd.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/rect.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/math/box/object_impl.hpp>


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
	SGE_CAMERA_SYMBOL
	explicit
	parameters(
		sge::input::mouse::device &,
		sge::input::keyboard::device &,
		renderer::projection::near const &,
		renderer::projection::far const &,
		sge::camera::is_active const &);

	SGE_CAMERA_SYMBOL
	sge::input::mouse::device &
	mouse() const;

	SGE_CAMERA_SYMBOL
	sge::input::keyboard::device &
	keyboard() const;

	SGE_CAMERA_SYMBOL
	parameters &
	zoom_speed(
		ortho_freelook::zoom_speed const &);

	SGE_CAMERA_SYMBOL
	ortho_freelook::zoom_speed const &
	zoom_speed() const;

	SGE_CAMERA_SYMBOL
	parameters &
	action_mapping(
		action::mapping const &);

	SGE_CAMERA_SYMBOL
	action::mapping const &
	action_mapping() const;

	SGE_CAMERA_SYMBOL
	parameters &
	pan_speed(
		ortho_freelook::pan_speed const &);

	SGE_CAMERA_SYMBOL
	ortho_freelook::pan_speed const &
	pan_speed() const;

	SGE_CAMERA_SYMBOL
	parameters &
	projection_rectangle(
		renderer::projection::rect const &);

	SGE_CAMERA_SYMBOL
	ortho_freelook::optional_projection_rectangle const &
	projection_rectangle() const;

	SGE_CAMERA_SYMBOL
	renderer::projection::near const &
	near() const;

	SGE_CAMERA_SYMBOL
	renderer::projection::far const &
	far() const;

	SGE_CAMERA_SYMBOL
	sge::camera::is_active const &
	is_active() const;

	SGE_CAMERA_SYMBOL
	~parameters();
private:
	sge::input::mouse::device &mouse_;
	sge::input::keyboard::device &keyboard_;
	ortho_freelook::zoom_speed zoom_speed_;
	ortho_freelook::pan_speed pan_speed_;
	ortho_freelook::optional_projection_rectangle projection_rectangle_;
	renderer::projection::near near_;
	renderer::projection::far far_;
	sge::camera::is_active is_active_;
	ortho_freelook::action::mapping action_mapping_;
};
}
}
}

#endif

