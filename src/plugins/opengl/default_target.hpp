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
#include <sge/renderer/target.hpp>
#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/pixel_pos.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/raw_value.hpp>
#include <fcppt/container/raw_vector_decl.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/math/dim/basic_decl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{

class default_target
:
	public sge::renderer::target
{
	FCPPT_NONCOPYABLE(default_target)
public:
	default_target(
		dim_type const &,
		renderer::bit_depth::type
	);

	~default_target();

	void
	pos(
		renderer::pixel_pos const &
	);

	void
	dim(
		dim_type const &
	);
private:
	image::view::const_object const
	lock(
		renderer::lock_rect const &dest
	) const;

	void
	unlock() const;

	dim_type const
	dim() const;

	GLenum
	format() const;

	GLenum
	format_type() const;

	typedef fcppt::container::raw_vector<
		renderer::raw_value
	> buffer_type;

	mutable buffer_type buffer_;

	renderer::pixel_pos pos_;

	dim_type dim_;

	renderer::size_type const stride_;
};

}
}

#endif
