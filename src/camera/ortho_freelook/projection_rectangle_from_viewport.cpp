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


#include <sge/camera/ortho_freelook/object.hpp>
#include <sge/camera/ortho_freelook/projection_rectangle_from_viewport.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/math/box/structure_cast.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/tr1/functional.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::camera::ortho_freelook::projection_rectangle_from_viewport::projection_rectangle_from_viewport(
	sge::camera::ortho_freelook::object &_camera,
	sge::renderer::device &_renderer,
	sge::viewport::manager &_viewport_manager)
:
	camera_(
		_camera),
	renderer_(
		_renderer),
	viewport_callback_connection_(
		_viewport_manager.manage_callback(
			std::tr1::bind(
				&projection_rectangle_from_viewport::viewport_callback,
				this)))
{
}

FCPPT_PP_POP_WARNING

sge::camera::ortho_freelook::projection_rectangle_from_viewport::~projection_rectangle_from_viewport()
{
}

void
sge::camera::ortho_freelook::projection_rectangle_from_viewport::viewport_callback()
{
	camera_.projection_rectangle(
		fcppt::math::box::structure_cast<sge::renderer::projection::rect>(
			renderer_.onscreen_target().viewport().get()));
}
