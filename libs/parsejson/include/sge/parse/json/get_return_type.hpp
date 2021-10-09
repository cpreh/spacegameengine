//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_JSON_GET_RETURN_TYPE_HPP_INCLUDED
#define SGE_PARSE_JSON_GET_RETURN_TYPE_HPP_INCLUDED

#include <fcppt/reference_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::parse::json
{

template <typename T, typename Arg>
using get_return_type = fcppt::reference<std::conditional_t<std::is_const_v<Arg>, T const, T>>;

}

#endif
