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


#include "../default_target.hpp"
#include "../common.hpp"
#include "../fbo_functions.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <sge/exception.hpp>
#include <fcppt/text.hpp>
#include <boost/cstdint.hpp>

sge::opengl::default_target::default_target(
	dim_type const & dim_,
	renderer::bit_depth::type const depth_
)
:
	pos_(renderer::pixel_pos::null()),
	dim_(dim_),
	depth_(depth_)
{}

void
sge::opengl::default_target::pos(
	renderer::pixel_pos const &p
)
{
	pos_ = p;
}

void
sge::opengl::default_target::dim(
	dim_type const &d)
{
	dim_ = d;
}

sge::renderer::pixel_pos const
sge::opengl::default_target::pos() const
{
	return pos_;
}

sge::renderer::target::dim_type const
sge::opengl::default_target::dim() const
{
	return dim_;
}

void
sge::opengl::default_target::bind_me() const
{
	unbind_fbo();
}

sge::opengl::default_target::size_type
sge::opengl::default_target::stride() const
{
	switch(depth_)
	{
	case renderer::bit_depth::depth16:
		return sizeof(boost::uint16_t);
	case renderer::bit_depth::depth32:
		return sizeof(boost::uint32_t);
	}

	throw exception(
		FCPPT_TEXT("Invalid bit_depth in ogl::default_target!")
	);
}

// currently 16bit and 32bit framebuffers are supported
// GL_UNSIGNED_BYTE is enough to read 32bit values so take this

GLenum
sge::opengl::default_target::format() const
{
	return GL_RGBA;
}

GLenum
sge::opengl::default_target::format_type() const
{
	return GL_UNSIGNED_BYTE;
}
