//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_JSON_CONFIG_MERGE_COMMAND_LINE_PARAMETERS_HPP_INCLUDED
#define SGE_PARSE_JSON_CONFIG_MERGE_COMMAND_LINE_PARAMETERS_HPP_INCLUDED

#include <sge/parse/json/object.hpp>
#include <sge/parse/json/detail/symbol.hpp>
#include <fcppt/args_vector.hpp>

namespace sge::parse::json::config
{

SGE_PARSE_JSON_DETAIL_SYMBOL
sge::parse::json::object
merge_command_line_parameters(sge::parse::json::object, fcppt::args_vector const &);

}

#endif
