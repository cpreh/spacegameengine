#ifndef SGE_PROCESS_OUTPUT_HPP_INCLUDED
#define SGE_PROCESS_OUTPUT_HPP_INCLUDED

#include <sge/process/symbol.hpp>
#include <sge/process/exit_code.hpp>
#include <fcppt/string.hpp>

namespace sge
{
namespace process
{
class output
{
public:
	SGE_PROCESS_SYMBOL explicit
	output(
		fcppt::string const &out,
		fcppt::string const &err,
		sge::process::exit_code);

	SGE_PROCESS_SYMBOL fcppt::string const &
	output_stream() const;

	SGE_PROCESS_SYMBOL fcppt::string const &
	error_stream() const;

	SGE_PROCESS_SYMBOL sge::process::exit_code
	exit_code() const;
private:
	fcppt::string output_stream_,error_stream_;
	sge::process::exit_code exit_code_;
};
}
}

#endif
