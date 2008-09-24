#include <sge/init.hpp>
#include <sge/systems.hpp>
#include <sge/iostream.hpp>
#include <sge/text.hpp>
#include <sge/exception.hpp>
#include <sge/renderer/vf/make_dynamic_format.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <boost/mpl/vector.hpp>
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

	typedef sge::renderer::vf::pos<
		sge::space_unit,
		1
	> pos_type;

	typedef sge::renderer::vf::format<
		boost::mpl::vector<
			pos_type
		>
	> format;

	sge::renderer::vf::make_dynamic_format<
		format>();
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
