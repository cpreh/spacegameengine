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


#ifndef SGE_CAMERA_ORTHO_FREELOOK_PARAMETERS_HPP_INCLUDED
#define SGE_CAMERA_ORTHO_FREELOOK_PARAMETERS_HPP_INCLUDED

#include <sge/camera/symbol.hpp>
#include <sge/camera/ortho_freelook/optional_projection_rect.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/mouse/device_fwd.hpp>
#include <sge/renderer/vector2.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/vector/object_impl.hpp>
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
		input::keyboard::device &);

	SGE_CAMERA_SYMBOL input::mouse::device &
	mouse() const;

	SGE_CAMERA_SYMBOL input::keyboard::device &
	keyboard() const;

	SGE_CAMERA_SYMBOL parameters &
	projection_rect(
		sge::renderer::projection::rect const &);

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

	SGE_CAMERA_SYMBOL ortho_freelook::optional_projection_rect const
	projection_rect() const;

	SGE_CAMERA_SYMBOL renderer::projection::near const
	near() const;

	SGE_CAMERA_SYMBOL renderer::projection::far const
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
	ortho_freelook::optional_projection_rect rect_;
	renderer::projection::near near_;
	renderer::projection::far far_;
	renderer::vector2 zoom_to_zooming_speed_factor_;
	renderer::vector2 zoom_to_panning_speed_factor_;
	bool active_;
};
}
}
}

#endif
