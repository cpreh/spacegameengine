#ifndef SGE_GUI_WIDGETS_FWD_HPP_INCLUDED
#define SGE_GUI_WIDGETS_FWD_HPP_INCLUDED

#include <boost/mpl/vector.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
class edit;
class label;
class image_label;
class backdrop;

namespace buttons
{
class text;
class image;
}

typedef boost::mpl::vector<
	buttons::text,
	buttons::image,
	edit,
	label,
	image_label,
	backdrop> types;
}
}
}

#endif
