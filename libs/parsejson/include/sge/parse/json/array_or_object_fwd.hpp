//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_ARRAY_OR_OBJECT_FWD_HPP_INCLUDED
#define SGE_PARSE_JSON_ARRAY_OR_OBJECT_FWD_HPP_INCLUDED

#include <sge/parse/json/array_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>
#include <fcppt/variant/object_fwd.hpp>


namespace sge
{
namespace parse
{
namespace json
{

using
array_or_object
=
fcppt::variant::object<
	sge::parse::json::array,
	sge::parse::json::object
>;

}
}
}

#endif
