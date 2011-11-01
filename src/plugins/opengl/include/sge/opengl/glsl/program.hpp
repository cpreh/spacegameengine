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


#ifndef SGE_OPENGL_GLSL_PROGRAM_HPP_INCLUDED
#define SGE_OPENGL_GLSL_PROGRAM_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/glsl/program_base.hpp>
#include <sge/opengl/glsl/program_holder.hpp>
#include <sge/opengl/glsl/shader_base_fwd.hpp>
#include <sge/renderer/stage.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/glsl/program.hpp>
#include <sge/renderer/glsl/shader_fwd.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <sge/renderer/glsl/uniform/variable_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace opengl
{
namespace glsl
{

template<
	typename Environment
>
class program
:
	public renderer::glsl::program,
	public program_base
{
	FCPPT_NONCOPYABLE(
		program
	);
public:
	explicit program(
		opengl::context::object &
	);

	~program();

	// public interface for the renderer device
	void
	use() const;

	void
	unuse() const;
private:
	// overridden functions
	renderer::glsl::uniform::variable_ptr const
	uniform(
		renderer::glsl::string const &
	);

	void
	vertex_declaration(
		renderer::vertex_declaration const &
	);

	void
	attach_shader(
		sge::renderer::glsl::shader const &
	);

	void
	detach_shader(
		sge::renderer::glsl::shader const &
	);

	void
	color_surface_location(
		renderer::stage,
		renderer::glsl::string const &
	);

	void
	link();

	fcppt::string const
	info_log() const;

	// internal functions
	typedef typename Environment::handle handle;

	typedef glsl::shader_base<
		Environment
	> shader_type;

	void
	do_use(
		handle
	) const;

	typedef typename Environment::uniform_context uniform_context;

	typedef glsl::program_holder<
		Environment
	> holder;

	holder const holder_;

	uniform_context const &uniform_context_;
};

}
}
}

#endif
