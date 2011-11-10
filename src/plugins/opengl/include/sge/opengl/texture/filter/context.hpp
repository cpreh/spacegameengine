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

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/texture/filter/context_fwd.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/texture/filter/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/index_map_decl.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{
namespace filter
{

class context
:
	public opengl::context::base
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	context();

	~context();

	renderer::texture::filter::object const &
	get(
		renderer::texture::stage
	);

	bool
	set(
		renderer::texture::stage,
		renderer::texture::filter::object const &
	);

	typedef void needs_before;

	static opengl::context::id const static_id;
private:
	renderer::texture::filter::object &
	get_mutable(
		renderer::texture::stage
	);

	typedef fcppt::container::index_map<
		renderer::texture::filter::object
	> filter_map;

	filter_map filters_;
};

}
}
}
}

#endif
