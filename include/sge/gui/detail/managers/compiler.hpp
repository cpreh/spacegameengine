#ifndef SGE_GUI_DETAIL_MANAGERS_COMPILER_HPP_INCLUDED
#define SGE_GUI_DETAIL_MANAGERS_COMPILER_HPP_INCLUDED

#include <sge/gui/detail/managers/fwd.hpp>
#include <sge/gui/detail/submanager.hpp>
#include <sge/gui/widget_fwd.hpp>
#include <set>

namespace sge
{
namespace gui
{
namespace detail
{
namespace managers
{
class compiler : public submanager
{
	public:
	compiler(mouse &,render &);
	void add(widget &);
	void update();
	void remove(widget &);
	void invalidate(widget &);
	private:
	typedef std::set<widget*> recompile_container;

	mouse &mouse_;
	render &render_;
	recompile_container recompiles;
	recompile_container deleted;

	bool has_parent(widget const &,widget const &);
};
}
}
}
}

#endif
