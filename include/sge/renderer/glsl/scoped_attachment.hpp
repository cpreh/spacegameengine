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


#ifndef SGE_RENDERER_GLSL_SCOPED_ATTACHMENT_HPP_INCLUDED
#define SGE_RENDERER_GLSL_SCOPED_ATTACHMENT_HPP_INCLUDED

#include <sge/renderer/glsl/scoped_attachment_fwd.hpp>
#include <sge/renderer/glsl/program_fwd.hpp>
#include <sge/renderer/glsl/shader_fwd.hpp>
#include <sge/renderer/symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace renderer
{
namespace glsl
{

class scoped_attachment
{
	FCPPT_NONCOPYABLE(
		scoped_attachment
	);
public:
	SGE_RENDERER_SYMBOL
	scoped_attachment(
		sge::renderer::glsl::program &,
		sge::renderer::glsl::shader const &
	);

	SGE_RENDERER_SYMBOL
	~scoped_attachment();
private:
	sge::renderer::glsl::program &program_;

	sge::renderer::glsl::shader const &shader_;
};

}
}
}

#endif
