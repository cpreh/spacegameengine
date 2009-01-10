#ifndef SGE_GUI_DETAIL_UPDATE_MANAGER_HPP_INCLUDED
#define SGE_GUI_DETAIL_UPDATE_MANAGER_HPP_INCLUDED

#include "manager_fwd.hpp"
#include "../widget_fwd.hpp"
#include <set>

namespace sge
{
namespace gui
{
namespace detail
{
class update_manager
{
	public:
	update_manager(mouse_manager &,render_manager &);
	void add(widget &);
	void draw();
	void remove(widget &);
	private:
	typedef std::set<widget*> recompile_container;

	mouse_manager &mouse;
	render_manager &render;
	recompile_container recompiles;

	bool has_parent(widget const &,widget const &);
};
}
}
}

#endif
