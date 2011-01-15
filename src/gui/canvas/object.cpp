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


#include "log.hpp"
#include <sge/gui/canvas/object.hpp>
#include <sge/gui/unit.hpp>
#include <sge/gui/log.hpp>
#include <sge/image2d/view/to_const.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/text.hpp>

sge::gui::canvas::object::object(
	image &_texture
)
:
	texture_(_texture),
	view_(texture_.view())
{
}

sge::gui::canvas::object::~object()
{}

sge::gui::dim const
sge::gui::canvas::object::size() const
{
	return texture_.size();
}

sge::gui::rect const
sge::gui::canvas::object::area() const
{
	return
		rect(
			point::null(),
			size()
		);
}

sge::gui::image_view &sge::gui::canvas::object::view()
{
	return view_;
}

sge::gui::const_image_view const
sge::gui::canvas::object::view() const
{
	return
		sge::image2d::view::to_const(
			view_
		);
}
