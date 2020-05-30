//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_CONST_OPTIONAL_OBJECT_REF_FWD_HPP_INCLUDED
#define SGE_PARSE_JSON_CONST_OPTIONAL_OBJECT_REF_FWD_HPP_INCLUDED

#include <sge/parse/json/object_fwd.hpp>
#include <fcppt/optional/reference_fwd.hpp>


namespace sge
{
namespace parse
{
namespace json
{

using
const_optional_object_ref
=
fcppt::optional::reference<
	sge::parse::json::object const
>;

}
}
}

#endif
