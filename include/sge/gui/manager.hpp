#ifndef SGE_GUI_MANAGER_HPP_INCLUDED
#define SGE_GUI_MANAGER_HPP_INCLUDED

#include "detail/managers/keyboard.hpp"
#include "detail/managers/mouse.hpp"
#include "detail/managers/update.hpp"
#include "detail/managers/render.hpp"
#include "detail/managers/time.hpp"
#include "timer/callback.hpp"
#include "timer/fwd.hpp"
#include "types.hpp"
#include "skin.hpp"
#include "widget_fwd.hpp"
#include "timer/fwd.hpp"
#include "../renderer/device_fwd.hpp"
#include "../renderer/texture_fwd.hpp"
#include "../input/system_fwd.hpp"
#include "../input/key_pair.hpp"
#include "../font/system_fwd.hpp"
#include "../font/metrics_fwd.hpp"
#include "../sprite/object.hpp"
#include "../sprite/system.hpp"
#include "../time/resolution.hpp"
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
