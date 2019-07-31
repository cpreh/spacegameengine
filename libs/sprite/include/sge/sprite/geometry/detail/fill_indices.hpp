//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_FILL_INDICES_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_FILL_INDICES_HPP_INCLUDED

#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/lock_segment.hpp>
#include <sge/renderer/index/scoped_lock.hpp>
#include <sge/renderer/index/any/generate.hpp>
#include <sge/renderer/index/any/make_view.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/index_count.hpp>
#include <sge/sprite/buffers/slice_impl.hpp>
#include <sge/sprite/geometry/detail/index_generator.hpp>


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
void
fill_indices(
	sge::sprite::count const _sprite_count,
	sge::sprite::buffers::slice<
		Choices
	> const &_slice
)
{
	sge::renderer::index::scoped_lock const lock(
		_slice.index_buffer(),
		sge::renderer::lock_segment{
			sge::renderer::lock_segment::vector{
				_slice.first_index().get()
			},
			sge::renderer::lock_segment::dim{
				sge::sprite::buffers::index_count<
					Choices
				>(
					_sprite_count
				).get()
			}
		},
		sge::renderer::lock_mode::writeonly
	);

	sge::renderer::index::any::generate(
		sge::renderer::index::any::make_view(
			lock.value()
		),
		sge::sprite::geometry::detail::index_generator<
			Choices
		>()
	);
}

}
}
}
}

#endif
