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


#include "log.hpp"
#include <sge/gui/log.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/global.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/text.hpp>

fcppt::log::object &
sge::gui::canvas::global_log()
{
	static fcppt::log::object global(
		fcppt::log::parameters::inherited(
			sge::gui::global_log(),
			FCPPT_TEXT("canvas")
		)
	);

	return global;
}
