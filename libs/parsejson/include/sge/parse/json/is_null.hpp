//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_JSON_IS_NULL_HPP_INCLUDED
#define SGE_PARSE_JSON_IS_NULL_HPP_INCLUDED

#include <sge/parse/json/value_fwd.hpp>
#include <sge/parse/json/detail/symbol.hpp>

namespace sge::parse::json
{

SGE_PARSE_JSON_DETAIL_SYMBOL bool is_null(sge::parse::json::value const &);

}

#endif
