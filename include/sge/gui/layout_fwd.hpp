#ifndef SGE_GUI_LAYOUT_FWD_HPP_INCLUDED
#define SGE_GUI_LAYOUT_FWD_HPP_INCLUDED

#include "../auto_ptr.hpp" 

namespace sge
{
namespace gui
{
class layout;

typedef auto_ptr<layout> layout_auto_ptr;
typedef layout* layout_ptr;
typedef layout const * const_layout_ptr;
}
}

#endif
