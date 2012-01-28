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


#ifndef SGE_SPRITE_RENDER_RANGE_PART_DECL_HPP_INCLUDED
#define SGE_SPRITE_RENDER_RANGE_PART_DECL_HPP_INCLUDED

#include <sge/renderer/first_index.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/primitive_count.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/texture/const_planar_ptr.hpp>
#include <sge/sprite/texture_level.hpp>
#include <sge/sprite/detail/render/range_part_object.hpp>
#include <sge/sprite/render/range_part_fwd.hpp>


namespace sge
{
namespace sprite
{
namespace render
{

template<
	typename Choices
>
class range_part
{
public:
	typedef typename sge::sprite::detail::render::range_part_object<
		Choices
	>::type range_part_object;

	explicit
	range_part(
		range_part_object const &
	);

	sge::renderer::first_index const
	first_index() const;

	sge::renderer::first_vertex const
	first_vertex() const;

	sge::renderer::vertex_count const
	vertex_count() const;

	sge::renderer::primitive_count const
	primitive_count() const;

	template<
		sge::sprite::texture_level Level
	>
	sge::renderer::texture::const_planar_ptr const
	texture_level() const;
private:
	range_part_object object_;
};

}
}
}

#endif
