//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_STATE_DETAIL_PARAMETERS_INIT_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_PARAMETERS_INIT_HPP_INCLUDED

#include <fcppt/optional/object_impl.hpp>
#include <fcppt/record/element.hpp>

namespace sge::sprite::state::detail
{

struct parameters_init
{
  template <typename Type, typename Label>
  fcppt::optional::object<Type>
  operator()(fcppt::record::element<Label, fcppt::optional::object<Type>>) const
  {
    return fcppt::optional::object<Type>();
  }
};

}

#endif
