#ifndef SGE_GUI_WIDGETS_FWD_HPP_INCLUDED
#define SGE_GUI_WIDGETS_FWD_HPP_INCLUDED

#include <boost/mpl/vector.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
class button;
class edit;
class label;
class image_label;
class backdrop;

typedef boost::mpl::vector<
	button,
	edit,
	label,
	image_label,
	backdrop> types;
}
}
}

#endif
