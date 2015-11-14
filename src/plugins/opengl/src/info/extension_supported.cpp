/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either extension_supported 2
of the License, or (at your option) any later extension_supported.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/opengl/extension_supported.hpp>
#include <sge/opengl/info/extension.hpp>
#include <sge/opengl/info/extension_set.hpp>
#include <sge/opengl/info/extension_supported.hpp>


bool
sge::opengl::info::extension_supported(
	sge::opengl::info::extension_set const &_extensions,
	sge::opengl::info::extension const &_extension
)
{
	return
		sge::opengl::extension_supported(
			_extensions,
			_extension
		);
}
