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


#include "../handle_bit_depth.hpp"
#include <GL/glx.h>
#include <sge/renderer/exception.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/text.hpp>

namespace
{

void
add_bit_depth(
	sge::opengl::glx::visual_attribute_array &,
	int r,
	int g,
	int b
);

}

void
sge::opengl::glx::handle_bit_depth(
	visual_attribute_array &_ret,
	renderer::bit_depth::type const _depth
)
{
	switch(
		_depth
	)
	{
	case renderer::bit_depth::depth16:
		add_bit_depth(_ret, 5, 6, 5); // TODO: what can we choose from here?
		return;
	case renderer::bit_depth::depth32:
		add_bit_depth(_ret, 8, 8, 8);
		return;
	}

	throw sge::renderer::exception(
		FCPPT_TEXT("Invalid bit_depth!")
	);
}

namespace
{

void
add_bit_depth(
	sge::opengl::glx::visual_attribute_array &ret,
	int const r,
	int const g,
	int const b
)
{
	ret.push_back(GLX_RED_SIZE);
	ret.push_back(r);
	ret.push_back(GLX_BLUE_SIZE);
	ret.push_back(g);
	ret.push_back(GLX_GREEN_SIZE);
	ret.push_back(b);
}

}
