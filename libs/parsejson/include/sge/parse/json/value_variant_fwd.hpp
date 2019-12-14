//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_VALUE_VARIANT_FWD_HPP_INCLUDED
#define SGE_PARSE_JSON_VALUE_VARIANT_FWD_HPP_INCLUDED

#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/array_fwd.hpp>
#include <sge/parse/json/float_type.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/null.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/object_fwd.hpp>
#include <sge/parse/json/value_fwd.hpp>
#include <fcppt/variant/object_fwd.hpp>


namespace sge
{
namespace parse
{
namespace json
{

typedef
fcppt::variant::object<
	sge::parse::json::object,
	sge::parse::json::array,
	bool,
	sge::charconv::utf8_string,
	sge::parse::json::int_type,
	sge::parse::json::float_type,
	sge::parse::json::null
>
value_variant;

}
}
}

#endif
