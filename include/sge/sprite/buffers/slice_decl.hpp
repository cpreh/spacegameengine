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


#ifndef SGE_SPRITE_BUFFERS_SLICE_DECL_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_SLICE_DECL_HPP_INCLUDED

#include <sge/renderer/first_index.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/index_buffer_fwd.hpp>
#include <sge/renderer/vertex_buffer_fwd.hpp>
#include <sge/sprite/buffers/object.hpp>
#include <sge/sprite/buffers/offset_object.hpp>
#include <sge/sprite/buffers/slice_fwd.hpp>
#include <sge/sprite/render/range_part_fwd.hpp>
#include <sge/sprite/render/range_part_vector.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace sprite
{
namespace buffers
{

template<
	typename Choices
>
class slice
{
	FCPPT_NONCOPYABLE(
		slice
	);
public:
	typedef typename sge::sprite::buffers::object<
		Choices
	>::type object;

	typedef typename sge::sprite::buffers::offset_object<
		Choices
	>::type offset_object;

	typedef typename sge::sprite::render::range_part_vector<
		Choices
	>::type range_part_vector;

	slice(
		object const &,
		offset_object const &
	);

	~slice();

	sge::renderer::vertex_buffer &
	vertex_buffer() const;

	sge::renderer::index_buffer &
	index_buffer() const;

	sge::renderer::first_vertex const
	first_vertex() const;

	sge::renderer::first_index const
	first_index() const;

	range_part_vector &
	part_vector();

	object const &
	buffer_object() const;

	void
	reset(
		object const &,
		offset_object const &
	);
private:
	object object_;

	offset_object offset_object_;

	range_part_vector part_vector_;
};

}
}
}

#endif
