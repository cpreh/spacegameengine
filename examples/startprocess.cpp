#include <sge/process/call.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/algorithm/map.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <string>
#include <exception>
#include <cstdlib>

int main(
	int argc,
	char *argv[])
try
{
	if (argc == 1)
	{
		fcppt::io::cout 
			<< FCPPT_TEXT("usage: ") 
			<< argv[0] 
			<< FCPPT_TEXT(" <process-to-start> <arguments-to-process>\n");
		return EXIT_FAILURE;
	}

	sge::process::output const out = 
		sge::process::call(
			fcppt::algorithm::map<sge::process::argument_list>(
				boost::make_iterator_range(
					// This +1 is important, else it's a recursive call (literally :P)
					argv+1,
					argv + argc),
				boost::bind(
					&fcppt::from_std_string,
					_1,
					std::locale())));

	fcppt::io::cout 
		<< FCPPT_TEXT("Standard output: \n")
		<< FCPPT_TEXT("\n--------------------------------\n")
		<< out.output_stream()
		<< FCPPT_TEXT("\n--------------------------------\n")
		<< FCPPT_TEXT("Standard error:")
		<< FCPPT_TEXT("\n--------------------------------\n")
		<< out.error_stream()
		<< FCPPT_TEXT("\n--------------------------------\n")
		<< FCPPT_TEXT("Exit code: " )
		<< out.exit_code()
		<< FCPPT_TEXT("\n");
}
catch (fcppt::exception const &e)
{
	fcppt::io::cout << FCPPT_TEXT("fcppt::exception caught: ") << e.string() << FCPPT_TEXT("\n");
	return EXIT_FAILURE;
}
catch (std::exception const &e)
{
	std::cout << "std::exception caught: " << e.what() << "\n";
	return EXIT_FAILURE;
}
