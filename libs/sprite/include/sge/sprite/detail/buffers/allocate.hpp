//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
