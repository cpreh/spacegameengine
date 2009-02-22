#ifndef SGE_GUI_WIDGETS_EDIT_HPP_INCLUDED
#define SGE_GUI_WIDGETS_EDIT_HPP_INCLUDED

#include "../detail/cursor_delegate.hpp"
#include "../widget.hpp"
#include "../timer/fwd.hpp"
#include "../events/fwd.hpp"
#include "../../renderer/image.hpp"
#include "../../font/metrics_fwd.hpp"
#include "../../signals/signal.hpp"
#include "../../export.hpp"

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

	SGE_SYMBOL edit(
		parent_data,
		line_type,
		dim const &desired_size,
		font::metrics_ptr = font::metrics_ptr());
	
	SGE_SYMBOL string const text() const;
	SGE_SYMBOL void text(string const &);
	SGE_SYMBOL font::metrics_ptr const font() const;
	SGE_SYMBOL point const &scroll_pos() const;
	SGE_SYMBOL dim const desired_size() const;
	SGE_SYMBOL image &text_buffer();
	SGE_SYMBOL image const &text_buffer() const;

	SGE_SYMBOL void process(events::keyboard_enter const &);
	SGE_SYMBOL key_handling::type process(events::key const &);
	SGE_SYMBOL void process(events::mouse_click const &);
	SGE_SYMBOL void process(events::keyboard_leave const &);

	SGE_SYMBOL void refresh() const;

	// will only be called for single_line
	signals::signal<void ()> return_pressed;
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
