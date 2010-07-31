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


#ifndef SGE_OPENGL_FBO_TARGET_HPP_INCLUDED
#define SGE_OPENGL_FBO_TARGET_HPP_INCLUDED

#include "fbo_target_fwd.hpp"
#include "texture_ptr.hpp"
#include "fbo.hpp"
#include <sge/renderer/target.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{

class fbo_target
:
	public sge::renderer::target
{
	FCPPT_NONCOPYABLE(fbo_target)
public:
	explicit fbo_target(
		sge::renderer::parameters const &,
		opengl::texture_ptr
	);

	~fbo_target();

	void
	bind_me() const;
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

	opengl::fbo fbo_;

	texture_ptr texture_;
};

}
}

#endif
