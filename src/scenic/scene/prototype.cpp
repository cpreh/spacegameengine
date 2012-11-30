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


#include <sge/scenic/scene/prototype.hpp>


sge::scenic::scene::prototype::prototype(
	sge::scenic::scene::camera_properties const &_camera,
	sge::scenic::render_context::fog::optional_properties const &_fog,
	sge::scenic::render_context::ambient_color const &_ambient_color)
:
	camera_(
		_camera),
	fog_(
		_fog),
	ambient_color_(
		_ambient_color),
	entities_(),
	lights_()
{
}

sge::scenic::scene::entity_sequence const &
sge::scenic::scene::prototype::entities() const
{
		return
			entities_;
}

sge::scenic::scene::entity_sequence &
sge::scenic::scene::prototype::entities()
{
		return
			entities_;
}

sge::scenic::render_context::light::sequence const &
sge::scenic::scene::prototype::lights() const
{
		return
			lights_;
}

sge::scenic::render_context::light::sequence &
sge::scenic::scene::prototype::lights()
{
		return
			lights_;
}

sge::scenic::scene::camera_properties const &
sge::scenic::scene::prototype::camera() const
{
		return
			camera_;
}

sge::scenic::render_context::fog::optional_properties const &
sge::scenic::scene::prototype::fog() const
{
		return
			fog_;
}

sge::scenic::render_context::ambient_color const &
sge::scenic::scene::prototype::ambient_color() const
{
		return
			ambient_color_;
}

sge::scenic::scene::prototype::~prototype()
{
}
