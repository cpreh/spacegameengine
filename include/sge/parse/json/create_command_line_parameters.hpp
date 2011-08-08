#ifndef SGE_PARSE_JSON_CREATE_COMMAND_LINE_PARAMETERS_HPP_INCLUDED
#define SGE_PARSE_JSON_CREATE_COMMAND_LINE_PARAMETERS_HPP_INCLUDED

#include <sge/parse/json/command_line_parameters.hpp>
#include <sge/parse/symbol.hpp>

namespace sge
{
namespace parse
{
namespace json
{
SGE_PARSE_SYMBOL json::command_line_parameters const
create_command_line_parameters(
	int argc,
	char *argv[]);
}
}
}

#endif
