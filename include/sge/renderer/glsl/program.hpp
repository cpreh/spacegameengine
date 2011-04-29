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


#ifndef SGE_RENDERER_GLSL_PROGRAM_HPP_INCLUDED
#define SGE_RENDERER_GLSL_PROGRAM_HPP_INCLUDED

#include <sge/renderer/glsl/program_fwd.hpp>
#include <sge/renderer/glsl/vertex_shader_ptr.hpp>
#include <sge/renderer/glsl/pixel_shader_ptr.hpp>
#include <sge/renderer/glsl/uniform/variable_ptr.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <sge/renderer/stage_type.hpp>
#include <sge/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/string.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace renderer
{
namespace glsl
{

class SGE_CLASS_SYMBOL program
{
	FCPPT_NONCOPYABLE(
		program
	);
protected:
	SGE_SYMBOL program();
public:
	virtual glsl::uniform::variable_ptr const
	uniform(
		glsl::string const &
	) = 0;

	virtual void
	vertex_shader(
		glsl::vertex_shader_ptr
	) = 0;

	virtual void
	pixel_shader(
		glsl::pixel_shader_ptr
	) = 0;

	virtual void
	color_surface_location(
		renderer::stage_type,
		glsl::string const &
	) = 0;

	virtual void
	link() = 0;

	virtual fcppt::string const
	info_log() const = 0;

	SGE_SYMBOL virtual ~program();
};

}
}
}

#endif
