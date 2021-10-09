//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_BUFFERS_OBJECT_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_OBJECT_HPP_INCLUDED

#include <sge/sprite/detail/buffers/object.hpp>

namespace sge::sprite::buffers
{

template <typename Choices>
using object = typename sge::sprite::detail::buffers::object<Choices>::type;

}

#endif
