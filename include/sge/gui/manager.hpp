#ifndef SGE_GUI_MANAGER_HPP_INCLUDED
#define SGE_GUI_MANAGER_HPP_INCLUDED

#include <sge/gui/detail/managers/keyboard.hpp>
#include <sge/gui/detail/managers/mouse.hpp>
#include <sge/gui/detail/managers/compiler.hpp>
#include <sge/gui/detail/managers/render.hpp>
#include <sge/gui/detail/managers/time.hpp>
#include <sge/gui/timer/callback.hpp>
#include <sge/gui/timer/fwd.hpp>
#include <sge/gui/skin.hpp>
#include <sge/gui/widget_fwd.hpp>
#include <sge/gui/timer/fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/texture_fwd.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/font/system_fwd.hpp>
#include <sge/font/metrics_fwd.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/system.hpp>
#include <sge/time/resolution.hpp>
#include <sge/image/loader_fwd.hpp>
#include <sge/gui/export.hpp>
#include <sge/noncopyable.hpp>
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
		sge::image::loader_ptr,
		input::system_ptr,
		font::system_ptr,
		skin_ptr,
		cursor_ptr);
	SGE_GUI_SYMBOL ~manager();
	SGE_GUI_SYMBOL void dirty(
		widget &,
		rect const &);
	SGE_GUI_SYMBOL void invalidate(
		widget &);
	SGE_GUI_SYMBOL timer::object_ptr const register_timer(
		time::resolution const &,
		timer::callback);
	SGE_GUI_SYMBOL void update();
	SGE_GUI_SYMBOL void draw();
	SGE_GUI_SYMBOL sge::gui::cursor const &cursor() const;
	SGE_GUI_SYMBOL font::metrics_ptr const standard_font();
	SGE_GUI_SYMBOL sge::gui::skin &skin();
	SGE_GUI_SYMBOL sge::gui::skin  const &skin() const;
	SGE_GUI_SYMBOL sge::sprite::object &connected_sprite(
		widget &);

	SGE_GUI_SYMBOL detail::managers::keyboard &keyboard();
	private:
	friend class widget;

	renderer::device_ptr const rend;
	sge::image::loader_ptr const il;
	input::system_ptr const is;
	font::system_ptr const fs;
	font::metrics_ptr const standard_font_;

	skin_ptr skin_;
	cursor_ptr cursor_;

	detail::managers::mouse    mouse_;
	detail::managers::render   render_;
	detail::managers::keyboard keyboard_;
	detail::managers::compiler compiler_;
	detail::managers::time     timer_;

	typedef std::vector<detail::submanager*> submanager_container;
	submanager_container submanagers;

	// this is called by widget's constructor and destructor
	void add(widget &);
	void remove(widget &);

	// this is called by widget's size/pos/.. function (if it encounters a top
	// level widget)
	void resize(
		widget &,
		dim const &);
	void reposition(
		widget &,
		point const &);
	void activation(
		widget &,
		activation_state::type);
};
}
}

#endif
