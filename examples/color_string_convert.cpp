#include <sge/image/color/any/print.hpp>
#include <sge/image/color/any/from_string.hpp>
#include <sge/image/exception.hpp>
#include <fcppt/io/cout.hpp>
#include <ostream>
#include <fcppt/text.hpp>
#include <cstddef>

int
main(
	int const argc,
	char *argv[])
try
{
	if(argc != 2)
	{
		fcppt::io::cout() << FCPPT_TEXT("Usage: ") << argv[0] << FCPPT_TEXT(" <color-string>\n");
		return EXIT_FAILURE;
	}
	fcppt::io::cout() << sge::image::color::any::from_string(argv[1]) << FCPPT_TEXT("\n");
	return EXIT_SUCCESS;
}
catch(
	 sge::image::exception const &e)
{
	 fcppt::io::cout() << e.string() << FCPPT_TEXT("\n");
	 return EXIT_FAILURE;
}
