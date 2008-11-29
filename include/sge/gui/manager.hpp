#ifndef SGE_GUI_MANAGER_HPP_INCLUDED
#define SGE_GUI_MANAGER_HPP_INCLUDED

#include "detail/keyboard_manager.hpp"
#include "detail/mouse_manager.hpp"
#include "detail/update_manager.hpp"
#include "types.hpp"
#include "skin.hpp"
#include "widget_fwd.hpp"
#include "widgets/container_fwd.hpp"
#include "../renderer/device_fwd.hpp"
#include "../renderer/texture_fwd.hpp"
#include "../input/system_fwd.hpp"
#include "../input/key_pair.hpp"
#include "../font/system_fwd.hpp"
#include "../font/metrics_fwd.hpp"
#include "../sprite/object.hpp"
#include "../sprite/system.hpp"
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
		image::loader_ptr,
		input::system_ptr,
		font::system_ptr,
		skin_ptr);
	SGE_SYMBOL void invalidate(rect const &);
	SGE_SYMBOL void invalidate(widget &);
	SGE_SYMBOL void draw();
	SGE_SYMBOL font::metrics_ptr const standard_font();
	SGE_SYMBOL skin_ptr const skin();

	private:
	friend class widget;
	friend class widgets::container;

	struct widget_data
	{
		widget_data(
			widget&,
			renderer::texture_ptr,
			sprite::object const &);

		widget *ptr;
		renderer::texture_ptr texture;
		sprite::object spr;
	};

	typedef std::vector<widget_data> widget_container;
	typedef std::vector<rect> dirt_container;
	typedef std::set<widget*> recompile_container;

	// engine relevant stuff
	renderer::device_ptr const rend;
	image::loader_ptr const il;
	input::system_ptr const is;
	font::system_ptr const fs;
	font::metrics_ptr const standard_font_;
	sprite::system ss;

	// other internal stuff
	widget_container widgets_;
	dirt_container dirt_;
	recompile_container recompiles_;

	skin_ptr skin_;

	// focus
	detail::mouse_manager mouse_;
	detail::keyboard_manager keyboard_;

	// this is called by widget's constructor and destructor
	void add(widget &);
	void remove(widget &);

	// this is called by widget's size/pos function (if it encounters a top level widget)
	void resize(widget &,dim const &);
	void reposition(widget &,point const &);

	// internal search functions (just convenience)
	widget_data &data(widget &);
	widget_container::iterator data_iterator(widget &);
	widget_data &parent_widget_data(widget &);
	detail::keyboard_manager &keyboard();

	void redraw_dirt();
	void recompile();
};
}
}

#endif
