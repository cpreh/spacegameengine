//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_GEOMETRY_SORT_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_SORT_HPP_INCLUDED

namespace sge::sprite::geometry
{

template <typename Range, typename Compare>
void sort(Range const &_range, Compare const &_compare)
{
  _range.sort(_compare);
}

}

#endif
