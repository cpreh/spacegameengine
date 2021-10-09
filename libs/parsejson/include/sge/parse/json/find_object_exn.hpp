//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_JSON_FIND_OBJECT_EXN_HPP_INCLUDED
#define SGE_PARSE_JSON_FIND_OBJECT_EXN_HPP_INCLUDED

#include <sge/parse/json/object_fwd.hpp>
#include <sge/parse/json/path_fwd.hpp>
#include <sge/parse/json/detail/symbol.hpp>
#include <fcppt/reference_impl.hpp>

namespace sge::parse::json
{

SGE_PARSE_JSON_DETAIL_SYMBOL
fcppt::reference<sge::parse::json::object const>
find_object_exn(fcppt::reference<sge::parse::json::object const>, sge::parse::json::path const &);

SGE_PARSE_JSON_DETAIL_SYMBOL
fcppt::reference<sge::parse::json::object>
find_object_exn(fcppt::reference<sge::parse::json::object>, sge::parse::json::path const &);

}

#endif
