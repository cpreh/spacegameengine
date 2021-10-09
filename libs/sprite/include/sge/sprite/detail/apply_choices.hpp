//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_APPLY_CHOICES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_APPLY_CHOICES_HPP_INCLUDED

#include <fcppt/mpl/list/object.hpp>

namespace sge::sprite::detail
{

template <typename Choices, typename Functions>
struct apply_choices;

// TODO(philipp): Can we do this in a better way?
template <typename Choices, typename... Functions>
struct apply_choices<Choices, fcppt::mpl::list::object<Functions...>>
{
  using type = fcppt::mpl::list::object<typename Functions ::template apply<Choices>::type...>;
};

}

#endif
