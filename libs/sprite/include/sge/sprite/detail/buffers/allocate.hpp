/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_DETAIL_BUFFERS_ALLOCATE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_BUFFERS_ALLOCATE_HPP_INCLUDED

#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/object.hpp>
#include <sge/sprite/buffers/parameters.hpp>
#include <sge/sprite/buffers/roles/index_buffer.hpp>
#include <sge/sprite/buffers/roles/vertex_buffer.hpp>
#include <sge/sprite/detail/buffers/allocate_indices.hpp>
#include <sge/sprite/detail/buffers/allocate_vertices.hpp>
#include <sge/sprite/detail/config/needs_index_buffer.hpp>
#include <fcppt/not.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace buffers
{

template<
	typename Choices
>
inline
std::enable_if_t<
	sge::sprite::detail::config::needs_index_buffer<
		Choices
	>::value,
	sge::sprite::buffers::object<
		Choices
	>
>
allocate(
	sge::sprite::buffers::parameters const &_parameters,
	sge::sprite::count const _num_sprites,
	sge::renderer::resource_flags_field const &_resource_flags
)
{
	return
		sge::sprite::buffers::object<
			Choices
		>{
			sge::sprite::buffers::roles::vertex_buffer{} =
				sge::sprite::detail::buffers::allocate_vertices<
					Choices
				>(
					_parameters,
					_num_sprites,
					_resource_flags
				),
			sge::sprite::buffers::roles::index_buffer{} =
				sge::sprite::detail::buffers::allocate_indices<
					Choices
				>(
					_parameters.device(),
					_num_sprites,
					_resource_flags
				)
		};
}

template<
	typename Choices,
	typename Buffers
>
inline
std::enable_if_t<
	fcppt::not_(
		sge::sprite::detail::config::needs_index_buffer<
			Choices
		>::value
	),
	sge::sprite::buffers::object<
		Choices
	>
>
allocate(
	sge::sprite::buffers::parameters const &_parameters,
	sge::sprite::count const _num_sprites,
	sge::renderer::resource_flags_field const &_resource_flags
)
{
	return
		sge::sprite::buffers::object<
			Choices
		>(
			sge::sprite::buffers::roles::vertex_buffer{} =
				sge::sprite::detail::buffers::allocate_vertices<
					Choices
				>(
					_parameters,
					_num_sprites,
					_resource_flags
				)
		);
}

}
}
}
}

#endif
