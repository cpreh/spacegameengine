//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_BUFFERS_ZERO_OFFSET_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_ZERO_OFFSET_HPP_INCLUDED

#include <sge/sprite/buffers/offset_object.hpp>
#include <sge/sprite/detail/buffers/zero_offset.hpp>

namespace sge::sprite::buffers
{

template <typename Choices>
inline sge::sprite::buffers::offset_object<Choices> zero_offset()
{
  return sge::sprite::detail::buffers::zero_offset<Choices>();
}

}

#endif
