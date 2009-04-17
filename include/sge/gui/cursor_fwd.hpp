#ifndef SGE_GUI_CURSOR_FWD_HPP_INCLUDED
#define SGE_GUI_CURSOR_FWD_HPP_INCLUDED

#include <sge/shared_ptr.hpp>

namespace sge
{
namespace gui
{
class cursor;

typedef shared_ptr<cursor> cursor_ptr;
typedef shared_ptr<cursor const> const_cursor_ptr;
}
}

#endif
