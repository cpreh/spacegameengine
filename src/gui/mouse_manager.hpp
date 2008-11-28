#ifndef SGE_GUI_DETAIL_MOUSE_MANAGER_HPP_INCLUDED
#define SGE_GUI_DETAIL_MOUSE_MANAGER_HPP_INCLUDED

namespace sge
{
namespace gui
{
namespace detail
{
class mouse_manager
{
	public:
	mouse_manager(
		widget_container &,
		input::system_ptr,
		image::loader_ptr,
		renderer::device_ptr,
		skin &);
	
	void add_widget(widget &);
	void remove_widget(widget &);
	private:
	typedef boost::ptr_vector<widget,boost::view_clone_allocator> widget_container;

	widget_container widgets;
	signals::scoped_connection ic;
	sprite::object cursor;
	sprite::point cursor_click;
	widget *focus;

	void input_callback(input::key_pair const &);
	void recalculate_focus();
	widget *recalculate_focus(widget &w,point const &);
	widget *do_recalculate_focus(widget &,point const &);
	widget *do_recalculate_focus(widgets::container &,point const &);
};
}
}
}

#endif
