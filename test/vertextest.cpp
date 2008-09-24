#include <sge/init.hpp>
#include <sge/systems.hpp>
#include <sge/iostream.hpp>
#include <sge/text.hpp>
#include <sge/exception.hpp>
#include <sge/renderer/vf/make_dynamic_format.hpp>
#include <ostream>
#include <exception>
#include <cstdlib>

int main()
try
{
	sge::systems sys;
	sys.init<sge::init::core>();
	sys.init<sge::init::renderer>(
		sge::renderer::screen_size_t(1024, 768));
	sys.init<sge::init::input>();
}
catch(sge::exception const &e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
