#include <sge/process/output.hpp>

sge::process::output::output(
	fcppt::string const &_output_stream,
	fcppt::string const &_error_stream,
	sge::process::exit_code const _exit_code)
:
	output_stream_(
		_output_stream),
	error_stream_(
		_error_stream),
	exit_code_(
		_exit_code)
{
}

fcppt::string const &
sge::process::output::output_stream() const
{
	return output_stream_;
}

fcppt::string const &
sge::process::output::error_stream() const
{
	return error_stream_;
}

sge::process::exit_code
sge::process::output::exit_code() const
{
	return exit_code_;
}
