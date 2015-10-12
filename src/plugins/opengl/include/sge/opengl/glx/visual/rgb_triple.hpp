/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_GLX_VISUAL_RGB_TRIPLE_HPP_INCLUDED
#define SGE_OPENGL_GLX_VISUAL_RGB_TRIPLE_HPP_INCLUDED

#include <sge/opengl/glx/visual/rgb_triple_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge
{
namespace opengl
{
namespace glx
{
namespace visual
{

class rgb_triple
{
	FCPPT_NONASSIGNABLE(
		rgb_triple
	);
public:
	FCPPT_MAKE_STRONG_TYPEDEF(
		int,
		red_bits
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		int,
		green_bits
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		int,
		blue_bits
	);

	rgb_triple(
		sge::opengl::glx::visual::rgb_triple::red_bits,
		sge::opengl::glx::visual::rgb_triple::green_bits,
		sge::opengl::glx::visual::rgb_triple::blue_bits
	);

	sge::opengl::glx::visual::rgb_triple::red_bits
	red() const;

	sge::opengl::glx::visual::rgb_triple::green_bits
	green() const;

	sge::opengl::glx::visual::rgb_triple::blue_bits
	blue() const;
private:
	sge::opengl::glx::visual::rgb_triple::red_bits const red_;

	sge::opengl::glx::visual::rgb_triple::green_bits const green_;

	sge::opengl::glx::visual::rgb_triple::blue_bits const blue_;
};

}
}
}
}

#endif
