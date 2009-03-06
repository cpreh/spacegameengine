#ifndef SGE_GUI_MANAGER_HPP_INCLUDED
#define SGE_GUI_MANAGER_HPP_INCLUDED

#include <sge/gui/detail/managers/keyboard.hpp>
#include <sge/gui/detail/managers/mouse.hpp>
#include <sge/gui/detail/managers/update.hpp>
#include <sge/gui/detail/managers/render.hpp>
#include <sge/gui/detail/managers/time.hpp>
#include <sge/gui/timer/callback.hpp>
#include <sge/gui/timer/fwd.hpp>
#include <sge/gui/types.hpp>
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
#include <sge/export.hpp>
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
	SGE_SYMBOL manager(
		renderer::device_ptr,
		sge::image::loader_ptr,
		input::system_ptr,
		font::system_ptr,
		skin_ptr);
	SGE_SYMBOL ~manager();
	SGE_SYMBOL void invalidate(
		widget &,
		rect const &);
	SGE_SYMBOL timer::object_ptr const register_timer(
		time::resolution const &,
		timer::callback);
	SGE_SYMBOL void draw();
	SGE_SYMBOL font::metrics_ptr const standard_font();
	SGE_SYMBOL skin_ptr const skin();
	SGE_SYMBOL const_skin_ptr const skin() const;

	SGE_SYMBOL detail::managers::keyboard &keyboard();
	private:
	friend class widget;

	renderer::device_ptr const rend;
	sge::image::loader_ptr const il;
	input::system_ptr const is;
	font::system_ptr const fs;
	font::metrics_ptr const standard_font_;

	skin_ptr skin_;

	detail::managers::mouse    mouse_;
	detail::managers::render   render_;
	detail::managers::keyboard keyboard_;
	detail::managers::update   updates_;
	detail::managers::time     timer_;

	std::vector<detail::submanager*> submanagers;

	// this is called by widget's constructor and destructor
	void add(widget &);
	void remove(widget &);

	// this is called by widget's size/pos/.. function (if it encounters a top
	// level widget)
	void resize(widget &,dim const &);
	void reposition(widget &,point const &);
	void activation(widget &,activation_state::type);
};
}
}

#endif
