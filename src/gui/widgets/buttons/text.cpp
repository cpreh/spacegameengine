/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/gui/widgets/buttons/text.hpp>
#include <sge/gui/widgets/parameters.hpp>
#include <sge/gui/events/key.hpp>
#include <sge/gui/manager.hpp>
#include <sge/input/key_type.hpp>
#include <sge/assert.hpp>

sge::gui::widgets::buttons::text::text(
	parent_data const &_parent,
	parameters _params,
	string const &_caption)
:
	base(
		_parent,
		_params
			.size_policy(
				sge::gui::size_policy(
					//axis_policy::can_grow,
					axis_policy::none,
					axis_policy::none))),
	  caption_(_caption)
{
}

sge::string const sge::gui::widgets::buttons::text::caption() const
{
	return caption_;
}
