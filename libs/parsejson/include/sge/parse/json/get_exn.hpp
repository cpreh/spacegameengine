//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_GET_EXN_HPP_INCLUDED
#define SGE_PARSE_JSON_GET_EXN_HPP_INCLUDED

#include <sge/parse/json/get_exn_message.hpp>
#include <sge/parse/json/detail/get_return_type.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>


namespace sge
{
namespace parse
{
namespace json
{

template<
	typename T,
	typename Arg
>
inline
sge::parse::json::detail::get_return_type<
	T,
	Arg
>
get_exn(
	Arg &_val
)
{
	return
		sge::parse::json::get_exn_message<
			T
		>(
			_val,
			[]{
				return
					fcppt::string{
						FCPPT_TEXT("")
					};
			}
		);
}

}
}
}

#endif
