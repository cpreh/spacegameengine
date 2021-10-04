//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_CONVERT_FROM_FWD_HPP_INCLUDED
#define SGE_PARSE_JSON_CONVERT_FROM_FWD_HPP_INCLUDED

#include <sge/parse/json/value_fwd.hpp>


namespace sge::parse::json
{

template<
	typename Result
>
decltype(
	auto
)
convert_from(
	sge::parse::json::value const &
);

}

#endif
