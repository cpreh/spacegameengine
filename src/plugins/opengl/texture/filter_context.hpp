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


#ifndef SGE_OPENGL_TEXTURE_FILTER_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_FILTER_CONTEXT_HPP_INCLUDED

#include "../context/base.hpp"
#include "../context/id.hpp"
#include "filter_context_fwd.hpp"
#include <sge/renderer/texture/filter/object.hpp>
#include <sge/renderer/stage.hpp>
#include <fcppt/container/index_map_decl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{
namespace texture
{

class filter_context
:
	public opengl::context::base
{
	FCPPT_NONCOPYABLE(
		filter_context
	);
public:
	filter_context();

	~filter_context();

	renderer::texture::filter::object const &
	get(
		renderer::stage
	);

	bool
	set(
		renderer::stage,
		renderer::texture::filter::object const &
	);

	typedef void needs_before;

	static opengl::context::id const static_id;
private:
	renderer::texture::filter::object &
	get_mutable(
		renderer::stage
	);

	typedef fcppt::container::index_map<
		renderer::texture::filter::object
	> filter_map;

	filter_map filters_;
};

}
}
}

#endif
