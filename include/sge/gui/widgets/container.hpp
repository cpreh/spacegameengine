#ifndef SGE_GUI_WIDGETS_CONTAINER_HPP_INCLUDED
#define SGE_GUI_WIDGETS_CONTAINER_HPP_INCLUDED

#include "../widget.hpp"
#include "../layout.hpp"
#include "../../export.hpp"

namespace sge
{
namespace gui
{
namespace widgets
{
class SGE_CLASS_SYMBOL container : public widget
{
	public:
	typedef boost::ptr_vector<widget,boost::view_clone_allocator> child_container;

	SGE_SYMBOL explicit container(parent_data);
	SGE_SYMBOL void add_child(widget &);
	SGE_SYMBOL void remove_child(widget &);
	child_container &children();
	child_container const &children() const;
	template<typename T>
	void layout() { layout_.reset(new T(*this)); }
	layout_ptr layout();
	const_layout_ptr layout() const;
	void size_hint(dim const &);
	dim const size_hint() const;
	SGE_SYMBOL void process(events::invalid_area const &);
	SGE_SYMBOL bool has_child(widget const &) const;
	private:
	void do_compile();

	child_container children_;
	layout_auto_ptr layout_;
	dim             size_hint_;
};
}
}
}

#endif
