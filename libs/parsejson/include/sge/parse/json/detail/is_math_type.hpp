//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_JSON_DETAIL_IS_MATH_TYPE_HPP_INCLUDED
#define SGE_PARSE_JSON_DETAIL_IS_MATH_TYPE_HPP_INCLUDED

#include <fcppt/math/size_type.hpp>
#include <fcppt/math/dim/object_fwd.hpp>
#include <fcppt/math/vector/object_fwd.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::parse::json::detail
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template <typename T>
struct is_math_type : std::false_type
{
};

template <typename T, fcppt::math::size_type N, typename S>
struct is_math_type<fcppt::math::vector::object<T, N, S>> : std::true_type
{
};

template <typename T, fcppt::math::size_type N, typename S>
struct is_math_type<fcppt::math::dim::object<T, N, S>> : std::true_type
{
};

FCPPT_PP_POP_WARNING

}

#endif
