#ifndef SGE_GUI_WIDGETS_EDIT_HPP_INCLUDED
#define SGE_GUI_WIDGETS_EDIT_HPP_INCLUDED

#include <sge/gui/detail/cursor_delegate.hpp>
#include <sge/gui/widget.hpp>
#include <sge/gui/timer/fwd.hpp>
#include <sge/gui/events/fwd.hpp>
#include <sge/renderer/image.hpp>
#include <sge/font/metrics_fwd.hpp>
#include <sge/signal/object.hpp>
#include <sge/gui/export.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
class SGE_CLASS_SYMBOL edit : public widget
{
	public:
	enum line_type { single_line,multi_line };

	SGE_GUI_SYMBOL edit(
		parent_data const &,
		parameters,
		line_type,
		dim const &desired_size,
		font::metrics_ptr = font::metrics_ptr());
	
	SGE_GUI_SYMBOL string const text() const;
	SGE_GUI_SYMBOL void text(string const &);
	SGE_GUI_SYMBOL font::metrics_ptr const font() const;
	SGE_GUI_SYMBOL point const &scroll_pos() const;
	SGE_GUI_SYMBOL dim const desired_size() const;
	SGE_GUI_SYMBOL image &text_buffer();
	SGE_GUI_SYMBOL image const &text_buffer() const;

	SGE_GUI_SYMBOL void process(events::keyboard_enter const &);
	SGE_GUI_SYMBOL key_handling::type process(events::key const &);
	SGE_GUI_SYMBOL void process(events::mouse_click const &);
	SGE_GUI_SYMBOL void process(events::keyboard_leave const &);

	SGE_GUI_SYMBOL void refresh() const;

	// will only be called for single_line
	signal::object<void ()> return_pressed;
	private:
	using widget::process;
	line_type type;
	string text_;
	font::metrics_ptr font_;
	dim desired_size_;
	timer::object_ptr timer_;
	bool cursor_visible_;
	mutable image text_buffer_;
	mutable point scroll_pos_;
	detail::cursor_delegate cursor;

	void blink_callback();
	void resize(dim const &) const;
};
}
}
}

#endif
