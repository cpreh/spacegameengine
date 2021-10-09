//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_STATE_DETAIL_OPTIONS_CLASS_ELEMENT_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_OPTIONS_CLASS_ELEMENT_HPP_INCLUDED

#include <fcppt/record/element.hpp>

namespace sge::sprite::state::detail
{

template <typename Type>
using options_class_element = fcppt::record::element<typename Type::role, bool>;

}

#endif
