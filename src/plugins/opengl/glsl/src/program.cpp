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


#include "../program.hpp"
#include "../attachment.hpp"
#include "../program_functions.hpp"
#include "../uniform/variable.hpp"
#include "../format_error.hpp"
#include <sge/renderer/glsl/exception.hpp>
#include <sge/text.hpp>
#include <sge/optional_impl.hpp>
#include <sge/string.hpp>
#include <sge/make_shared_ptr.hpp>
#include <sge/make_auto_ptr.hpp>
#include <sge/auto_ptr.hpp>
#include <sge/assert.hpp>

template<
	bool Native
>
sge::opengl::glsl::program<Native>::program(
	renderer::glsl::optional_string const &vs_source,
	renderer::glsl::optional_string const &ps_source)
:
	instance_(),
	attachments()
{
	SGE_ASSERT(
		vs_source || ps_source
	);

	if(vs_source)
		attach_shader(
			sge::make_shared_ptr<
				shader_type
			>(
				vertex_shader_type<Native>(),
				*vs_source
			)
		);

	if(ps_source)
		attach_shader(
			sge::make_shared_ptr<
				shader_type
			>(
				pixel_shader_type<Native>(),
				*ps_source
			)
		);

	link();
}

template<
	bool Native
>
sge::opengl::glsl::program<Native>::~program()
{}

template<
	bool Native
>
void sge::opengl::glsl::program<Native>::use(
	renderer::glsl::program_ptr const p)
{
	if(!p)
	{
		use_ffp();
		return;
	}

	dynamic_pointer_cast<
		program<Native>
	>(p)->use();
}

template<
	bool Native
>
void sge::opengl::glsl::program<Native>::attach_shader(
	shader_ptr const s)
{
	auto_ptr<
		attachment_type
	> a(
		sge::make_auto_ptr<
			attachment_type
		>(
			s,
			id()
		)
	);

	attachments.push_back(
		a
	);
}

template<
	bool Native
>
void sge::opengl::glsl::program<Native>::link()
{
	link_program<Native>(id());

	if(
		link_status<Native>(id()) == GL_FALSE
	)
		throw sge::renderer::glsl::exception(
			FCPPT_TEXT("Compiling a program failed:\n")
			+
			format_error(
				&program_info_log<
					Native
				>,
				id()
			)
		);
}

template<bool Native>
void sge::opengl::glsl::program<Native>::use()
{
	use_program<Native>(id());
}

template<bool Native>
sge::renderer::glsl::uniform::variable_ptr const
sge::opengl::glsl::program<Native>::uniform(
	renderer::glsl::string const &name)
{
	return make_shared_ptr<
		uniform::variable<
			Native
		>
	>(
		id(),
		name
	);
}

template<
	bool Native
>
void sge::opengl::glsl::program<Native>::use_ffp()
{
	use_program<Native>(0);
}

template<
	bool Native
>
typename sge::opengl::glsl::traits<Native>::handle
sge::opengl::glsl::program<Native>::id() const
{
	return instance_.id();
}

template class sge::opengl::glsl::program<true>;
template class sge::opengl::glsl::program<false>;
