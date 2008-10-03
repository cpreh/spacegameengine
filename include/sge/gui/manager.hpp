#ifndef SGE_GUI_MANAGER_HPP_INCLUDED
#define SGE_GUI_MANAGER_HPP_INCLUDED

#include "types.hpp"
#include "skin.hpp"
#include "../renderer/device.hpp"
#include "../input/system.hpp"
#include "../font/system.hpp"
#include "../sprite/object.hpp"
#include "../sprite/system.hpp"
#include "../scoped_connection.hpp"
#include "../image/loader.hpp"
#include "../export.hpp"

namespace sge
{
namespace gui
{
// forward declaration
class widget;

class manager
{
	public:
	SGE_SYMBOL manager(renderer::device_ptr,image::loader_ptr,input::system_ptr,font::system_ptr);
	SGE_SYMBOL void invalidate(rect const &);
	SGE_SYMBOL void draw();
	font::metrics_ptr const standard_font() { return standard_font_; }
	skin_ptr const skin() { return skin_; }

	private:
	friend class widget;

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

	// engine relevant stuff
	renderer::device_ptr const rend;
	image::loader_ptr const il;
	input::system_ptr const is;
	font::system_ptr const fs;
	font::metrics_ptr const standard_font_;
	scoped_connection ic;
	sprite::system ss;
	sge::sprite::object cursor;
	sge::sprite::point cursor_click;

	// other internal stuff
	widget_container widgets_;
	dirt_container dirt_;

	// focus
	widget *keyboard_focus;
	widget *mouse_focus;

	skin_ptr skin_;

	// this is called by widget's constructor and destructor
	void add(widget &);
	void remove(widget &);
	void compile(widget &);

	// this is called by widget's size/pos function (if it encounters a top level widget)
	void resize(widget &,dim const &);
	void reposition(widget &,point const &);

	// internal search functions (just convenience)
	widget_data &get_data(widget &);
	widget_container::iterator get_data_iterator(widget &);
	widget_data &parent_widget_data(widget &);
	void recalculate_mouse_focus();

	// registered input callback
	void input_callback(input::key_pair const &);

	void redraw_dirt();
};
}
}

#endif
