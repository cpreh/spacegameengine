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


#include "../on_not_supported.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

void
sge::opengl::on_not_supported(
	fcppt::string const &function,
	fcppt::string const &min_version,
	fcppt::string const &possible_extensions
)
{
	throw renderer::exception(
		FCPPT_TEXT("You tried to use the following functionality: \"")
		+ function
		+ FCPPT_TEXT("\" which is not supported by your implementation. opengl-")
		+ min_version
		+ FCPPT_TEXT(" is at least required. The possible extensions sge can use are: \"")
		+ possible_extensions
		+ FCPPT_TEXT("\".")
	);
}
