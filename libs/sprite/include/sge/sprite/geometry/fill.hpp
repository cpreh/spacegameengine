//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_GEOMETRY_FILL_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_FILL_HPP_INCLUDED

#include <sge/sprite/buffers/slice_fwd.hpp>
#include <sge/sprite/geometry/detail/fill.hpp>
#include <sge/sprite/render/range_impl.hpp>


namespace sge::sprite::geometry
{

template<
	typename Range,
	typename Compare,
	typename Choices
>
inline
sge::sprite::render::range<
	Choices
>
fill(
	Range const &_range,
	Compare const &_compare,
	sge::sprite::buffers::slice<
		Choices
	> const &_slice
)
{
	return
		sge::sprite::geometry::detail::fill(
			_range,
			_compare,
			_slice
		);
}

}

#endif
