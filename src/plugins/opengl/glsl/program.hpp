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


#ifndef SGE_OPENGL_GLSL_PROGRAM_HPP_INCLUDED
#define SGE_OPENGL_GLSL_PROGRAM_HPP_INCLUDED

#include "handle.hpp"
#include "attachment_fwd.hpp"
#include "program_instance.hpp"
#include <sge/renderer/glsl/program_ptr.hpp>
#include <sge/renderer/glsl/program.hpp>
#include <sge/renderer/glsl/optional_string.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

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
	public renderer::glsl::program
{
public:
	program(
		renderer::glsl::optional_string const &vs_source,
		renderer::glsl::optional_string const &ps_source
	);

	~program();

	static void
	use(
		renderer::glsl::program_ptr
	);
private:
	renderer::glsl::uniform::variable_ptr const
	uniform(
		renderer::glsl::string const &
	);

	fcppt::string const
	info_log() const;

	static void
	use_ffp();

	void
	use();

	handle
	id() const;

	void
	attach_shader(
		shader_ptr shader
	);

	void
	link();

	void
	do_link();

	GLint
	get_integer(
		GLenum
	) const;

	GLenum
	link_status() const;

	typedef typename Environment::handle handle;

	typedef glsl::shader<
		typename Environment::shader_environment_type
	> shader_type;

	typedef fcppt::shared_ptr<
		shared_type
	> shader_ptr;

	typedef glsl::shader<
		typename Environment::program_environment_type
	> attachment_type;

	typedef boost::ptr_vector<
		attachment_type
	> attachment_vector;

	handle const id_;

	attachment_vector attachments_;
};

}
}
}

#endif
