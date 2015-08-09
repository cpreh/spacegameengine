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


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_RENDER_PART_ELEMENT_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_RENDER_PART_ELEMENT_HPP_INCLUDED

#include <sge/renderer/index/first.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/deref_texture.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/texture_level.hpp>
#include <sge/sprite/buffers/index_count.hpp>
#include <sge/sprite/buffers/slice_impl.hpp>
#include <sge/sprite/buffers/vertex_count.hpp>
#include <sge/sprite/buffers/roles/first_index.hpp>
#include <sge/sprite/buffers/roles/first_vertex.hpp>
#include <sge/sprite/detail/roles/index_count.hpp>
#include <sge/sprite/detail/roles/texture.hpp>
#include <sge/sprite/detail/roles/vertex_count.hpp>
#include <sge/sprite/roles/texture.hpp>
#include <majutsu/get.hpp>
#include <majutsu/role.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace sprite
{
namespace geometry
{
namespace detail
{

template<
	typename Choices
>
class render_part_element
{
	FCPPT_NONASSIGNABLE(
		render_part_element
	);
public:
	typedef
	sge::sprite::buffers::slice<
		Choices
	>
	slice_type;

	typedef
	sge::sprite::object<
		Choices
	>
	object_type;

	render_part_element(
		slice_type const &_slice,
		sge::sprite::count const _offset,
		sge::sprite::count const _count,
		object_type const &_object
	)
	:
		slice_(
			_slice
		),
		offset_(
			_offset
		),
		count_(
			_count
		),
		object_(
			_object
		)
	{
	}

	template<
		typename Type
	>
	Type
	operator()(
		majutsu::role<
			Type,
			sge::sprite::detail::roles::vertex_count
		>
	) const
	{
		return
			sge::sprite::buffers::vertex_count<
				Choices
			>(
				count_
			);
	}

	template<
		typename Type
	>
	Type
	operator()(
		majutsu::role<
			Type,
			sge::sprite::buffers::roles::first_vertex
		>
	) const
	{
		return
			sge::renderer::vertex::first(
				slice_.first_vertex().get()
				+
				sge::sprite::buffers::vertex_count<
					Choices
				>(
					offset_
				).get()
			);
	}

	template<
		typename Type
	>
	Type
	operator()(
		majutsu::role<
			Type,
			sge::sprite::detail::roles::index_count
		>
	) const
	{
		return
			sge::sprite::buffers::index_count<
				Choices
			>(
				count_
			);
	}

	template<
		typename Type
	>
	Type
	operator()(
		majutsu::role<
			Type,
			sge::sprite::buffers::roles::first_index
		>
	) const
	{
		return
			sge::renderer::index::first(
				slice_.first_index().get()
				+
				sge::sprite::buffers::index_count<
					Choices
				>(
					offset_
				).get()
			);
	}

	template<
		typename Type,
		sge::sprite::texture_level Level
	>
	Type
	operator()(
		majutsu::role<
			Type,
			sge::sprite::detail::roles::texture<
				Level
			>
		>
	) const
	{
		return
			fcppt::make_cref(
				sge::sprite::deref_texture(
					majutsu::get<
						sge::sprite::roles::texture<
							Level
						>
					>(
						object_
					)
				).texture()
			);
	}
private:
	slice_type const &slice_;

	sge::sprite::count const offset_;

	sge::sprite::count const count_;

	object_type const &object_;
};

}
}
}
}

#endif
