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


#ifndef SGE_OPENGL_TEXTURE_SCOPED_WORK_BINDING_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_SCOPED_WORK_BINDING_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/binding.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/opengl/texture/scoped_work_binding_fwd.hpp>
#include <sge/opengl/texture/type.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class scoped_work_binding
:
	public sge::opengl::texture::binding
{
	FCPPT_NONCOPYABLE(
		scoped_work_binding
	);
public:
	scoped_work_binding(
		sge::opengl::context::object &,
		sge::opengl::texture::type,
		sge::opengl::texture::id
	);

	~scoped_work_binding();
private:
	void
	bind_id(
		sge::opengl::texture::id
	);

	sge::opengl::context::object &context_;

	sge::opengl::texture::id const previous_id_;

	sge::opengl::texture::type const type_;
};

}
}
}

#endif
