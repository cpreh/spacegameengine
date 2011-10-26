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


#ifndef SGE_OPENGL_TEXTURE_SCOPED_WORK_BIND_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_SCOPED_WORK_BIND_HPP_INCLUDED

#include <sge/opengl/texture/scoped_work_bind_fwd.hpp>
#include <sge/opengl/texture/bind_context_fwd.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/renderer/stage.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class scoped_work_bind
{
	FCPPT_NONCOPYABLE(
		scoped_work_bind
	);
public:
	scoped_work_bind(
		opengl::context::object &,
		opengl::texture::type,
		opengl::texture::id,
		renderer::stage
	);

	~scoped_work_bind();
private:
	opengl::context::object &context_;

	texture::bind_context &bind_context_;

	renderer::stage const stage_;
};

}
}
}

#endif
