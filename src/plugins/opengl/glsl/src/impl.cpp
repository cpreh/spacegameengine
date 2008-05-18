/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)
Copyright (C) 2007       Simon Stienen    (s.stienen@slashlife.org)

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


#include "../impl.hpp"
#include "../program.hpp"
#include "../../version.hpp"
#include "../../common.hpp"
#include <sge/once.hpp>

namespace
{

bool use_arb_shaders;

void initialize_glsl()
{
	SGE_FUNCTION_ONCE

	if(GLEW_VERSION_2_0)
		use_arb_shaders = false;
	else if(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
		use_arb_shaders = true;
	else
		sge::ogl::on_not_supported(
			SGE_TEXT("shader"),
			SGE_TEXT("2.0"),
			SGE_TEXT("gl_arb_vertex_shader && gl_arb_fragment_shader"));
}

}

const sge::glsl::program_ptr
sge::ogl::glsl::create_program_impl(
	const std::string& vs_source,
	const std::string& ps_source)
{
	initialize_glsl();
	return use_arb_shaders
		? sge::glsl::program_ptr(
			new program<false>(vs_source, ps_source))
		: sge::glsl::program_ptr(
			new program<true>(vs_source, ps_source));
}

void sge::ogl::glsl::set_program_impl(
	const sge::glsl::program_ptr prog)
{
	initialize_glsl();
	if(use_arb_shaders)
		program<false>::use(prog);
	else
		program<true>::use(prog);
}
