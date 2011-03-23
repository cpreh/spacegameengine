#ifndef SGE_LINE_DRAWER_RENDER_TO_SCREEN_HPP_INCLUDED
#define SGE_LINE_DRAWER_RENDER_TO_SCREEN_HPP_INCLUDED

#include <sge/renderer/device_ptr.hpp>
#include <sge/line_drawer/object_fwd.hpp>
#include <sge/line_drawer/symbol.hpp>

namespace sge
{
namespace line_drawer
{
SGE_LINE_DRAWER_SYMBOL void
render_to_screen(
	sge::renderer::device_ptr,
	object &);
}
}

#endif
