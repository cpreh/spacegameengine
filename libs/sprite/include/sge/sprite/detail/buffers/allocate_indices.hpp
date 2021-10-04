//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_BUFFERS_ALLOCATE_INDICES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_BUFFERS_ALLOCATE_INDICES_HPP_INCLUDED

#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/index/buffer.hpp>
#include <sge/renderer/index/buffer_parameters.hpp>
#include <sge/renderer/index/buffer_unique_ptr.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/index_count.hpp>


namespace sge::sprite::detail::buffers
{

template<
	typename Choices
>
sge::renderer::index::buffer_unique_ptr
allocate_indices(
	sge::renderer::device::core_ref const _renderer,
	sge::sprite::count const _num_sprites,
	sge::renderer::resource_flags_field const &_resource_flags
)
{
	return
		_renderer.get().create_index_buffer(
			sge::renderer::index::buffer_parameters(
				sge::renderer::index::dynamic::format::i16,
				sge::sprite::buffers::index_count<
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
