/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_GLSL_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_GLSL_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/glsl/context_fwd.hpp>
#include <sge/opengl/glsl/program_base_fwd.hpp>
#include <sge/renderer/glsl/const_optional_program_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace glsl
{

class context
:
	public opengl::context::base
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	context();

	~context();

	bool
	is_supported() const;

	bool
	is_native() const;

	void
	use(
		sge::renderer::glsl::const_optional_program const &
	);

	static opengl::context::id const static_id;

	typedef void needs_before;
private:
	bool const
		normal_shader_,
		arb_shader_;

	glsl::program_base const *last_program_;
};

}
}
}

#endif
