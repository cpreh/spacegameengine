#include <sge/iostream.hpp>
#include <sge/text.hpp>
#include <sge/exception.hpp>
#include <sge/typeswitch.hpp>
#include <sge/renderer/image_view_impl.hpp>
#include <boost/gil/extension/dynamic_image/any_image_view.hpp>
#include <boost/gil/extension/dynamic_image/image_view_factory.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/pixel.hpp>
#include <boost/gil/rgba.hpp>
#include <boost/mpl/vector.hpp>
#include <exception>
#include <ostream>
#include <cstdlib>

typedef boost::gil::any_image_view<
	boost::mpl::vector<
		boost::gil::rgba8_view_t
	>
> image_view;

typedef boost::gil::any_image_view<
	boost::mpl::vector<
		boost::gil::rgba8c_view_t
	>
> const_image_view;

typedef sge::uint8 pixel_channel_8;

typedef boost::gil::pixel<
	pixel_channel_8,
	boost::gil::rgba_layout_t
> rgba8_pixel;

int main()
try
{
	char testdata[4];
	image_view view(
		boost::gil::interleaved_view(
			1,
			1,
			reinterpret_cast<rgba8_pixel *>(testdata),
			4));
	const_image_view cview(view);
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
