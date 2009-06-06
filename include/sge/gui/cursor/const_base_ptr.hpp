#ifndef SGE_GUI_CURSOR_CONST_BASE_PTR_HPP_INCLUDED
#define SGE_GUI_CURSOR_CONST_BASE_PTR_HPP_INCLUDED

#include <sge/gui/cursor/base_fwd.hpp>
#include <sge/shared_ptr.hpp>

namespace sge
{
namespace gui
{
namespace cursor
{
typedef shared_ptr<base const> const_base_ptr;
}
}
}

#endif
