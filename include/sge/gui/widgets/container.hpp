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

	SGE_SYMBOL explicit container(parent_data,point const & = point(),dim const & = dim());
	SGE_SYMBOL void add_child(widget &);
	SGE_SYMBOL void remove_child(widget &);
	SGE_SYMBOL child_container &children() { return children_; }
	SGE_SYMBOL child_container const &children() const { return children_; }
	template<typename T>
	void layout() { layout_.reset(new T(*this)); }
	SGE_SYMBOL layout_ptr layout() { return layout_.get(); }
	SGE_SYMBOL const_layout_ptr layout() const { return layout_.get(); }
	SGE_SYMBOL dim const size_hint() const;
	SGE_SYMBOL void process(events::invalid_area const &);
	SGE_SYMBOL bool has_child(widget const &) const;
	private:
	void do_size(dim const &);
	void do_pos(point const &);
	void do_compile();
	widget *do_recalculate_focus(point const &);

	child_container children_;
	layout_auto_ptr layout_;
};
}
}
}

#endif
