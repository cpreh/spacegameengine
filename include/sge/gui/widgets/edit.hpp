#ifndef SGE_GUI_WIDGETS_TEXT_HPP_INCLUDED
#define SGE_GUI_WIDGETS_TEXT_HPP_INCLUDED

#include "../widget.hpp"
#include "../timer/fwd.hpp"
#include "../events/fwd.hpp"
#include "../../math/vector.hpp"
#include "../../renderer/image.hpp"
#include "../../font/metrics_fwd.hpp"
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
	SGE_SYMBOL edit(
		parent_data,
		dim const &desired_size,
		font::metrics_ptr = font::metrics_ptr());
	
	SGE_SYMBOL dim const size_hint() const;
	SGE_SYMBOL string const text() const;
	SGE_SYMBOL font::metrics_ptr const font() const;
	SGE_SYMBOL point const &scroll_pos() const;

	SGE_SYMBOL void process(events::keyboard_enter const &);
	SGE_SYMBOL key_handling::type process(events::key const &);
	SGE_SYMBOL void process(events::keyboard_leave const &);
	private:
	string text_;
	font::metrics_ptr font_;
	dim desired_size_;
	timer::object_ptr timer_;
	bool cursor_visible_;
	image buffer_;
	point scroll_pos_;

	void blink_callback();
	void resize(math::vector<bool,2> const &);
};
}
}
}

#endif
