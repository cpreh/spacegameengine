#include <sge/parse/json/create_command_line_parameters.hpp>
#include <sge/parse/json/command_line_parameters.hpp>
#include <fcppt/from_std_string.hpp>
#include <cstddef>

sge::parse::json::command_line_parameters const
sge::parse::json::create_command_line_parameters(
	int argc,
	char *argv[])
{
	json::command_line_parameters result(
		static_cast<json::command_line_parameters::size_type>(
			argc));
	for(
		json::command_line_parameters::size_type i = 
			0; 
		i < static_cast<json::command_line_parameters::size_type>(argc); 
		++i)
		result[i] = 
			fcppt::from_std_string(
				argv[static_cast<std::size_t>(i)]);
	return result;
}
