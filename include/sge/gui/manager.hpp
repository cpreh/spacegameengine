#ifndef SGE_GUI_MANAGER_HPP_INCLUDED
#define SGE_GUI_MANAGER_HPP_INCLUDED

#include <sge/gui/detail/managers/fwd.hpp>
#include <sge/gui/timer/callback.hpp>
#include <sge/gui/timer/fwd.hpp>
#include <sge/gui/skins/base.hpp>
#include <sge/gui/widgets/fwd.hpp>
#include <sge/gui/cursor_fwd.hpp>
#include <sge/gui/export.hpp>
#include <sge/gui/rect.hpp>
#include <sge/gui/point.hpp>
#include <sge/gui/activation_state.hpp>
#include <sge/gui/keyboard_focus.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/texture_fwd.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/system.hpp>
#include <sge/time/resolution.hpp>
#include <sge/image/loader_fwd.hpp>
#include <sge/noncopyable.hpp>
#include <sge/scoped_ptr.hpp>
#include <set>
#include <vector>

namespace sge
{
namespace gui
{
class manager 
{
	SGE_NONCOPYABLE(manager)
	public:
	SGE_GUI_SYMBOL manager(
		renderer::device_ptr,
		image::loader_ptr,
		input::system_ptr,
		skins::ptr,
		cursor_ptr);
	SGE_GUI_SYMBOL ~manager();
	SGE_GUI_SYMBOL void dirty(
		widgets::base &,
		rect const &);
	SGE_GUI_SYMBOL void invalidate(
		widgets::base &);
	SGE_GUI_SYMBOL timer::object_ptr const register_timer(
		time::resolution const &,
		timer::callback);
	SGE_GUI_SYMBOL void update();
	SGE_GUI_SYMBOL void draw();
	SGE_GUI_SYMBOL sge::gui::cursor const &cursor() const;
	SGE_GUI_SYMBOL skins::base &skin();
	SGE_GUI_SYMBOL skins::base const &skin() const;
	SGE_GUI_SYMBOL sprite::object &connected_sprite(
		widgets::base &);
	SGE_GUI_SYMBOL void request_keyboard_focus(
		widgets::base &);
	private:
	friend class widgets::base;

	renderer::device_ptr const rend;
	image::loader_ptr const il;
	input::system_ptr const is;

	skins::ptr skin_;
	cursor_ptr cursor_;

	// this is just to prevent the detail dependencies
	scoped_ptr<detail::managers::mouse> mouse_;
	scoped_ptr<detail::managers::render> render_;
	scoped_ptr<detail::managers::keyboard> keyboard_;
	scoped_ptr<detail::managers::compiler> compiler_;
	scoped_ptr<detail::managers::time> timer_;

	typedef std::vector<detail::submanager*> submanager_container;
	submanager_container submanagers;

	// this is called by widget's constructor and destructor
	void add(widgets::base &);
	void remove(widgets::base &);

	// this is called by widget's size/pos/.. function (if it encounters a top
	// level widget)
	void resize(
		widgets::base &,
		dim const &);
	void reposition(
		widgets::base &,
		point const &);
	void activation(
		widgets::base &,
		activation_state::type);
	void keyboard_focus(
		widgets::base &,
		keyboard_focus::type);
};
}
}

#endif
