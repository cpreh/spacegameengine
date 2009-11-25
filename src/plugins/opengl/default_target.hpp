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


#ifndef SGE_OPENGL_DEFAULT_TARGET_HPP_INCLUDED
#define SGE_OPENGL_DEFAULT_TARGET_HPP_INCLUDED

#include "common.hpp"
#include "target.hpp"
#include <sge/renderer/bit_depth.hpp>
#include <sge/math/vector/basic_decl.hpp>
#include <sge/math/dim/basic_decl.hpp>

namespace sge
{
namespace opengl
{

class default_target : public target {
public:
	default_target(
		dim_type const &,
		renderer::bit_depth::type);

	void pos(
		renderer::pixel_pos const &);
	void dim(
		dim_type const &);
private:
	renderer::pixel_pos const pos() const;
	dim_type const dim() const;

	void bind_me() const;
	size_type stride() const;
	GLenum format() const;
	GLenum format_type() const;

	renderer::pixel_pos pos_;
	dim_type dim_;
	renderer::bit_depth::type const depth_;
};

}
}

#endif
