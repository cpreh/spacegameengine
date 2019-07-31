//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_DETAIL_GET_RETURN_TYPE_HPP_INCLUDED
#define SGE_PARSE_JSON_DETAIL_GET_RETURN_TYPE_HPP_INCLUDED

#include <sge/parse/json/detail/get_return_type_impl.hpp>


namespace sge
{
namespace parse
{
namespace json
{
namespace detail
{

template<
	typename T,
	typename Arg
>
using get_return_type
=
typename
sge::parse::json::detail::get_return_type_impl<
	T,
	Arg
>::type;

}
}
}
}

#endif
