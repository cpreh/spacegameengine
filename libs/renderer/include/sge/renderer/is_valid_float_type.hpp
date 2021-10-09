//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_IS_VALID_FLOAT_TYPE_HPP_INCLUDED
#define SGE_RENDERER_IS_VALID_FLOAT_TYPE_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer
{

template <typename T>
using is_valid_float_type = std::disjunction<std::is_same<T, float>, std::is_same<T, double>>;

}

#endif
