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

typedef boost::mpl::vector<button,edit> types;
}
}
}

#endif
