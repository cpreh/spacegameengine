#ifndef SGE_GUI_DETAIL_UPDATE_MANAGER_HPP_INCLUDED
#define SGE_GUI_DETAIL_UPDATE_MANAGER_HPP_INCLUDED

namespace sge
{
namespace gui
{
namespace detail
{
class update_manager
{
	public:
	update_manager(mouse_manager &);
	void add(widget &);
	void draw();
	void remove(widget &);
	private:
	typedef std::set<widget*> recompile_container;

	mouse_manager &mouse;
	recompile_container recompiles;
};
}
}
}

#endif
