//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_MAKE_RENDER_PART_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_MAKE_RENDER_PART_HPP_INCLUDED

#include <sge/sprite/count.hpp>
#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/buffers/slice_fwd.hpp>
#include <sge/sprite/detail/offset.hpp>
#include <sge/sprite/detail/render/range_part_object.hpp>
#include <sge/sprite/geometry/detail/render_part_element.hpp>
#include <sge/sprite/render/range_part_impl.hpp>
#include <fcppt/record/init.hpp>


namespace sge::sprite::geometry::detail
{

template<
	typename Choices
>
inline
sge::sprite::render::range_part<
	Choices
>
make_render_part(
	sge::sprite::buffers::slice<
		Choices
	> const &_slice,
	sge::sprite::detail::offset const _offset,
	sge::sprite::count const _count,
	sge::sprite::object<
		Choices
	> const &_current
)
{
	return
		sge::sprite::render::range_part<
			Choices
		>(
			fcppt::record::init<
				typename
				sge::sprite::detail::render::range_part_object<
					Choices
				>::type
			>(
				sge::sprite::geometry::detail::render_part_element<
					Choices
				>(
					_slice,
					_offset,
					_count,
					_current
				)
			)
		);
}

}

#endif
