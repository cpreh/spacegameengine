#ifndef SGE_GUI_WIDGETS_CONTAINER_HPP_INCLUDED
#define SGE_GUI_WIDGETS_CONTAINER_HPP_INCLUDED

#include "../widget.hpp"
#include "../layout.hpp"

namespace sge
{
namespace gui
{
namespace widgets
{
class container : public widget
{
	public:
	typedef boost::ptr_vector<widget,boost::view_clone_allocator> child_container;

	explicit container(parent_data,point const & = point(),dim const & = dim());
	void add_child(widget &);
	void remove_child(widget &);
	child_container &children() { return children_; }
	child_container const &children() const { return children_; }
	template<typename T>
	void layout() { layout_.reset(new T(*this)); }
	layout_ptr layout() { return layout_.get(); }
	const_layout_ptr layout() const { return layout_.get(); }
	dim minimum_size() const;
	void process(events::invalid_area const &);
	bool has_child(widget const &) const;
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
