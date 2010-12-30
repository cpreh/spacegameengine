#ifndef SGE_PROCESS_CALL_HPP_INCLUDED
#define SGE_PROCESS_CALL_HPP_INCLUDED

#include <sge/process/symbol.hpp>
#include <sge/process/output.hpp>
#include <sge/process/argument_list.hpp>

namespace sge
{
namespace process
{
SGE_PROCESS_SYMBOL output const
call(
	argument_list const &);
}
}

#endif
