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


#ifndef SGE_OPENGL_GLSL_PROGRAM_HPP_INCLUDED
#define SGE_OPENGL_GLSL_PROGRAM_HPP_INCLUDED

#include "program_base.hpp"
#include "program_holder.hpp"
#include "attachment_fwd.hpp"
#include "../context/object_fwd.hpp"
#include "../common.hpp"
#include <sge/renderer/glsl/uniform/variable_ptr.hpp>
#include <sge/renderer/glsl/pixel_shader_ptr.hpp>
#include <sge/renderer/glsl/program.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <sge/renderer/glsl/vertex_shader_ptr.hpp>
#include <sge/renderer/glsl/shader_ptr.hpp>
#include <fcppt/auto_ptr.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/noncopyable.hpp>

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
	FCPPT_NONCOPYABLE(program)
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

	GLint
	location(
		sge::renderer::glsl::string const &
	) const;
private:
	// overridden functions
	renderer::glsl::uniform::variable_ptr const
	uniform(
		renderer::glsl::string const &
	);

	void
	vertex_shader(
		sge::renderer::glsl::vertex_shader_ptr
	);

	void
	pixel_shader(
		sge::renderer::glsl::pixel_shader_ptr
	);

	void
	link();

	fcppt::string const
	info_log() const;

	// internal functions

	typedef typename Environment::handle handle;

	void
	do_use(
		handle
	) const;

	typedef glsl::attachment<
		Environment
	> attachment_type;

	typedef fcppt::auto_ptr<
		attachment_type
	> attachment_auto_ptr;

	attachment_auto_ptr
	make_attachment(
		sge::renderer::glsl::shader_ptr
	);

	typedef fcppt::scoped_ptr<
		attachment_type
	> attachment_ptr;

	typedef typename Environment::uniform_context uniform_context;

	typedef glsl::program_holder<
		Environment
	> holder;

	holder const holder_;

	uniform_context const &uniform_context_;

	attachment_ptr
		vertex_shader_,
		pixel_shader_;
};

}
}
}

#endif
