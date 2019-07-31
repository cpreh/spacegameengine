//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_DETAIL_GET_RETURN_TYPE_IMPL_HPP_INCLUDED
#define SGE_PARSE_JSON_DETAIL_GET_RETURN_TYPE_IMPL_HPP_INCLUDED

#include <sge/parse/json/value_fwd.hpp>


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
struct get_return_type_impl;

template<
	typename T
>
struct get_return_type_impl<
	T,
	sge::parse::json::value
>
{
	typedef T &type;
};

template<
	typename T
>
struct get_return_type_impl<
	T,
	sge::parse::json::value const
>
{
	typedef T const &type;
};

}
}
}
}

#endif
