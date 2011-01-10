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


#include "../bit_depth.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

awl::window::bit_depth::type
sge::opengl::convert::bit_depth(
	sge::renderer::bit_depth::type const _mode
)
{
	switch(
		_mode
	)
	{
	case sge::renderer::bit_depth::depth16:
		return awl::window::bit_depth::depth16;
	case sge::renderer::bit_depth::depth32:
		return awl::window::bit_depth::depth32;
	}

	throw sge::renderer::exception(
		FCPPT_TEXT("Invalid bit_depth!")
	);
}
