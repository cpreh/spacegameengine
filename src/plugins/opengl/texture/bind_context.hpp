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


#ifndef SGE_OPENGL_TEXTURE_BIND_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BIND_CONTEXT_HPP_INCLUDED

#include "bind_context_fwd.hpp"
#include "base_fwd.hpp"
#include "id.hpp"
#include "optional_type.hpp"
#include "type.hpp"
#include "../context/base.hpp"
#include "../context/id.hpp"
#include "../context/object_fwd.hpp"
#include <sge/renderer/stage.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/container/index_map_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class bind_context
:
	public context::base
{
	FCPPT_NONCOPYABLE(
		bind_context
	);
public:
	bind_context();

	~bind_context();

	void
	bind_for_rendering(
		opengl::context::object &,
		opengl::texture::base const &,
		renderer::stage
	);

	void
	unbind_for_rendering(
		opengl::context::object &,
		renderer::stage
	);

	void
	bind_for_work(
		opengl::context::object &,
		texture::type,
		texture::id,
		renderer::stage
	);

	void
	unbind_for_work(
		opengl::context::object &,
		renderer::stage
	);

	opengl::texture::base const *
	render_texture(
		renderer::stage
	);

	typedef void needs_before;

	static context::id const static_id;
private:
	typedef fcppt::container::index_map<
		opengl::texture::base const *
	> texture_vector;

	typedef fcppt::container::index_map<
		texture::optional_type
	> texture_type_vector;

	texture_vector
		render_textures_,
		temp_textures_;

	texture_type_vector last_types_;
};

}
}
}

#endif
