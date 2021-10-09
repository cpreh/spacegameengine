//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_BUFFERS_OFFSET_OBJECT_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_OFFSET_OBJECT_HPP_INCLUDED

#include <sge/sprite/detail/buffers/offset_object.hpp>

namespace sge::sprite::buffers
{

template <typename Choices>
using offset_object = typename sge::sprite::detail::buffers::offset_object<Choices>::type;

}

#endif
