//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_INTRUSIVE_ORDERED_DETAIL_MAP_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_ORDERED_DETAIL_MAP_HPP_INCLUDED

#include <sge/sprite/intrusive/collection_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::intrusive::ordered::detail
{

template <typename Order, typename Choices>
using map = std::map<Order, fcppt::unique_ptr<sge::sprite::intrusive::collection<Choices>>>;

}

#endif
