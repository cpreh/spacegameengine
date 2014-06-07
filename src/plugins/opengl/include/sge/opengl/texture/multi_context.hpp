/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_TEXTURE_MULTI_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_MULTI_CONTEXT_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/texture/multi_context_fwd.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class multi_context
:
	public sge::opengl::context::system::base
{
	FCPPT_NONCOPYABLE(
		multi_context
	);
public:
	multi_context();

	~multi_context();

	bool
	is_supported() const;

	typedef PFNGLACTIVETEXTUREPROC gl_active_texture;

	typedef PFNGLCLIENTACTIVETEXTUREPROC gl_client_active_texture;

	gl_active_texture
	active_texture() const;

	gl_client_active_texture
	client_active_texture() const;

	sge::renderer::caps::texture_stages const
	max_level() const;

	typedef void parameter;

	static sge::opengl::context::system::id const static_id;
private:
	bool const
		is_native_,
		is_arb_;

	gl_active_texture const active_texture_;

	gl_client_active_texture const client_active_texture_;

	sge::renderer::caps::texture_stages const max_level_;
};

}
}
}

#endif
