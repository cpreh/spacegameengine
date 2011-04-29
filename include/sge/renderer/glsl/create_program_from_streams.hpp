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


#ifndef SGE_RENDERER_GLSL_CREATE_PROGRAM_FROM_STREAMS_HPP_INCLUDED
#define SGE_RENDERER_GLSL_CREATE_PROGRAM_FROM_STREAMS_HPP_INCLUDED

#include <sge/renderer/glsl/program_ptr.hpp>
#include <sge/renderer/glsl/optional_istream.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/symbol.hpp>

namespace sge
{
namespace renderer
{
namespace glsl
{

SGE_SYMBOL
glsl::program_ptr const
create_program_from_streams(
	sge::renderer::device &,
	glsl::optional_istream const &vertex_shader_source,
	glsl::optional_istream const &pixel_shader_source
);

}
}
}

#endif
