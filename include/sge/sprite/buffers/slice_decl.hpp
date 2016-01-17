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


#ifndef SGE_SPRITE_BUFFERS_SLICE_DECL_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_SLICE_DECL_HPP_INCLUDED

#include <sge/renderer/index/buffer_fwd.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/sprite/buffers/object.hpp>
#include <sge/sprite/buffers/offset_object.hpp>
#include <sge/sprite/buffers/slice_fwd.hpp>
#include <fcppt/reference_impl.hpp>


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
public:
	typedef
	sge::sprite::buffers::object<
		Choices
	>
	object;

	typedef
	fcppt::reference<
		object const
	>
	object_ref;

	typedef
	sge::sprite::buffers::offset_object<
		Choices
	>
	offset_object;

	slice(
		object_ref,
		offset_object
	);

	sge::renderer::vertex::buffer &
	vertex_buffer() const;

	sge::renderer::index::buffer &
	index_buffer() const;

	sge::renderer::vertex::first
	first_vertex() const;

	sge::renderer::index::first
	first_index() const;

	object const &
	buffer_object() const;
private:
	object_ref object_;

	offset_object offsets_;
};

}
}
}

#endif
