//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_BUFFERS_ALLOCATE_VERTICES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_BUFFERS_ALLOCATE_VERTICES_HPP_INCLUDED

#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/buffer_parameters.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/const_declaration_ref.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/vertex_count.hpp>
#include <sge/sprite/detail/vf/part_index.hpp>


namespace sge::sprite::detail::buffers
{

template<
	typename Choices
>
sge::renderer::vertex::buffer_unique_ptr
allocate_vertices(
	sge::renderer::device::core_ref const _renderer,
	sge::renderer::vertex::const_declaration_ref const _vertex_declaration,
	sge::sprite::count const _num_sprites,
	sge::renderer::resource_flags_field const &_resource_flags
)
{
	return
		_renderer.get().create_vertex_buffer(
			sge::renderer::vertex::buffer_parameters(
				_vertex_declaration,
				sge::sprite::detail::vf::part_index(),
				sge::sprite::buffers::vertex_count<
					Choices
				>(
					_num_sprites
				),
				_resource_flags
			)
		);
}

}

#endif
