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


#ifndef SGE_OPENGL_TEXTURE_BIND_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BIND_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/device/base.hpp>
#include <sge/opengl/context/device/id.hpp>
#include <sge/opengl/texture/base_fwd.hpp>
#include <sge/opengl/texture/bind_context_fwd.hpp>
#include <sge/opengl/texture/const_optional_base_ref.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/index_map_decl.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class bind_context
:
	public sge::opengl::context::device::base
{
	FCPPT_NONCOPYABLE(
		bind_context
	);
public:
	bind_context();

	~bind_context();

	sge::opengl::texture::const_optional_base_ref const
	stage(
		sge::renderer::texture::stage
	) const;

	void
	stage(
		sge::renderer::texture::stage,
		sge::opengl::texture::const_optional_base_ref const &
	);

	typedef void needs_before;

	static
	sge::opengl::context::device::id const
	static_id;
private:
	typedef fcppt::container::index_map<
		sge::opengl::texture::const_optional_base_ref
	> texture_map;

	mutable texture_map map_;
};

}
}
}

#endif
