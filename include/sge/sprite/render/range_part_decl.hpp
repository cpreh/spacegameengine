/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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

#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
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

	sge::renderer::index::first const
	first_index() const;

	sge::renderer::vertex::first const
	first_vertex() const;

	sge::renderer::vertex::count const
	vertex_count() const;

	sge::renderer::index::count const
	index_count() const;

	template<
		sge::sprite::texture_level Level
	>
	sge::renderer::texture::planar const *
	texture_level() const;
private:
	range_part_object object_;
};

}
}
}

#endif
