#ifndef SGE_GUI_LAYOUT_FWD_HPP_INCLUDED
#define SGE_GUI_LAYOUT_FWD_HPP_INCLUDED

#include <boost/scoped_ptr.hpp>
#include <memory>

namespace sge
{
namespace gui
{
class layout;

typedef boost::scoped_ptr<layout> layout_auto_ptr;
typedef layout* layout_ptr;
typedef layout const * const_layout_ptr;
}
}

#endif
