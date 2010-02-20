#ifndef SGE_CONSOLE_OUTPUT_LINE_SEQUENCE_HPP_HPP_INCLUDED
#define SGE_CONSOLE_OUTPUT_LINE_SEQUENCE_HPP_HPP_INCLUDED

#include <sge/console/pointed_history.hpp>
#include <fcppt/string.hpp>

namespace sge
{
namespace console
{
typedef 
pointed_history<fcppt::string> 
output_line_sequence;
}
}

#endif
