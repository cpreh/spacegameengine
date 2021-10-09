//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_REPETITION_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_REPETITION_HPP_INCLUDED

#include <sge/sprite/roles/repetition.hpp>
#include <sge/sprite/types/repetition.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/record/element.hpp>

namespace sge::sprite::detail::primitives
{

template <typename Choices>
struct texture_repetition
{
  using type = fcppt::mpl::list::object<fcppt::record::element<
      sge::sprite::roles::repetition,
      sge::sprite::types::repetition<typename Choices::type_choices>>>;
};

}

#endif
