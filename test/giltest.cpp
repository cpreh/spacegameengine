#include <sge/systems.hpp>
#include <sge/init.hpp>
#include <sge/iostream.hpp>
#include <sge/exception.hpp>
#include <sge/raw_vector_impl.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/color.hpp>
#include <sge/renderer/texture_filter.hpp>
#include <sge/renderer/image_view.hpp>
#include <boost/gil/image_view_factory.hpp>
#include <exception>
#include <ostream>
#include <cstdlib>

int main()
try
{
	sge::systems sys;
	sys.init<sge::init::core>();
	sys.init<sge::init::renderer>(1024, 768);
	
	const sge::renderer::device_ptr rend = sys.renderer;

	sge::raw_vector<unsigned char> raw_data(256 * 256 * 4);

	rend->create_texture(
		sge::renderer::const_image_view(
			boost::gil::interleaved_view(
				256,
				256,
				reinterpret_cast<sge::renderer::rgba8_pixel const *>(
					raw_data.data()),
				256 * 4)),
			sge::renderer::linear_filter);
}
catch(const sge::exception& e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
catch(const std::exception& e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
