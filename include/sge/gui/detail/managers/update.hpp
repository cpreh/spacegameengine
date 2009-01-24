#ifndef SGE_GUI_DETAIL_MANAGERS_UPDATE_HPP_INCLUDED
#define SGE_GUI_DETAIL_MANAGERS_UPDATE_HPP_INCLUDED

#include "fwd.hpp"
#include "../submanager.hpp"
#include "../../widget_fwd.hpp"
#include <set>

namespace sge
{
namespace gui
{
namespace detail
{
namespace managers
{
class update : public submanager
{
	public:
	update(mouse &,render &);
	void add(widget &);
	void draw();
	void remove(widget &);
	private:
	typedef std::set<widget*> recompile_container;

	mouse &mouse_;
	render &render_;
	recompile_container recompiles;

	bool has_parent(widget const &,widget const &);
};
}
}
}
}

#endif
