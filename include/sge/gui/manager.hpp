#ifndef SGE_GUI_MANAGER_HPP_INCLUDED
#define SGE_GUI_MANAGER_HPP_INCLUDED

#include "detail/keyboard_manager.hpp"
#include "detail/mouse_manager.hpp"
#include "detail/update_manager.hpp"
#include "detail/render_manager.hpp"
#include "detail/time_manager.hpp"
#include "timer/callback.hpp"
#include "timer/fwd.hpp"
#include "types.hpp"
#include "skin.hpp"
#include "widget_fwd.hpp"
#include "timer/fwd.hpp"
#include "widgets/container_fwd.hpp"
#include "../renderer/device_fwd.hpp"
#include "../renderer/texture_fwd.hpp"
#include "../input/system_fwd.hpp"
#include "../input/key_pair.hpp"
#include "../font/system_fwd.hpp"
#include "../font/metrics_fwd.hpp"
#include "../sprite/object.hpp"
#include "../sprite/system.hpp"
#include "../time/resolution.hpp"
#include "../signals/scoped_connection.hpp"
#include "../image/loader_fwd.hpp"
#include "../export.hpp"
#include <set>
#include <vector>

namespace sge
{
namespace gui
{
class manager
{
	public:
	SGE_SYMBOL manager(
		renderer::device_ptr,
		sge::image::loader_ptr,
		input::system_ptr,
		font::system_ptr,
		skin_ptr);
	SGE_SYMBOL void invalidate(rect const &);
	SGE_SYMBOL void invalidate(widget &);
	SGE_SYMBOL timer::object_ptr const register_timer(
		time::resolution const &,
		timer::callback);
	SGE_SYMBOL void draw();
	SGE_SYMBOL font::metrics_ptr const standard_font();
	SGE_SYMBOL skin_ptr const skin();

	private:
	friend class widget;
	friend class widgets::container;

	renderer::device_ptr const rend;
	sge::image::loader_ptr const il;
	input::system_ptr const is;
	font::system_ptr const fs;
	font::metrics_ptr const standard_font_;

	skin_ptr skin_;

	detail::mouse_manager mouse_;
	detail::render_manager render_;
	detail::keyboard_manager keyboard_;
	detail::update_manager updates_;
	detail::time_manager timer_;

	// this is called by widget's constructor and destructor
	void add(widget &);
	void remove(widget &);

	// this is called by widget's size/pos function (if it encounters a top level widget)
	void resize(widget &,dim const &);
	void reposition(widget &,point const &);

	detail::keyboard_manager &keyboard();
};
}
}

#endif
