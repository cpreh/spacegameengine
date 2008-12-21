#ifndef SGE_GUI_WIDGET_HPP_INCLUDED
#define SGE_GUI_WIDGET_HPP_INCLUDED

#include "events/fwd.hpp"
#include "keyboard_focus.hpp"
#include "key_handling.hpp"
#include "types.hpp"
#include "layout_fwd.hpp"
#include "manager_fwd.hpp"
#include "size_policy.hpp"
#include "../renderer/image.hpp"
#include "../export.hpp"

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>

namespace sge
{
namespace gui
{
class SGE_CLASS_SYMBOL widget : boost::noncopyable
{
	public:
	typedef sge::gui::size_policy size_policy_t;
	typedef boost::ptr_vector<widget,boost::view_clone_allocator> child_container;

	class parent_data
	{
		widget *const widget_;
		manager &manager_;

		public:
		SGE_SYMBOL explicit parent_data(widget &);
		SGE_SYMBOL explicit parent_data(manager &);

		widget *parent_widget() const { return widget_; }
		manager &parent_manager() const { return manager_; }
	};

	SGE_SYMBOL explicit widget(
		parent_data,
		size_policy_t const & = size_policy_t::default_policy,
		keyboard_focus::type receives_keys = keyboard_focus::ignore);

	// getters and setters go here
	SGE_SYMBOL point const &pos() const;
	SGE_SYMBOL dim const &size() const;
	SGE_SYMBOL image &buffer() const;

	// parent stuff
	SGE_SYMBOL manager &parent_manager();
	SGE_SYMBOL manager const &parent_manager() const;
	
	SGE_SYMBOL widget *parent_widget();
	SGE_SYMBOL widget const *parent_widget() const;

	SGE_SYMBOL size_policy_t const &size_policy() const;
	SGE_SYMBOL void size_policy(size_policy_t const &s);

	SGE_SYMBOL gui::keyboard_focus::type keyboard_focus() const;
	SGE_SYMBOL void keyboard_focus(keyboard_focus::type);

	SGE_SYMBOL child_container &children();
	SGE_SYMBOL child_container const &children() const;

	SGE_SYMBOL void add_child(widget &);
	SGE_SYMBOL void remove_child(widget &);

	template<typename T>
	void layout() { layout_.reset(new T(*this)); }

	SGE_SYMBOL layout_ptr layout();
	SGE_SYMBOL const_layout_ptr layout() const;

	SGE_SYMBOL bool has_child(widget const &) const;

	SGE_SYMBOL void size(dim const &);
	SGE_SYMBOL void pos(point const &);
	SGE_SYMBOL void compile();

	virtual dim const size_hint() const;
	virtual void process(events::invalid_area const &);
	virtual void process(events::mouse_enter const &);
	virtual void process(events::mouse_leave const &);
	virtual void process(events::mouse_move const &);
	virtual void process(events::mouse_click const &);
	virtual key_handling::type process(events::key const &);
	virtual void process(events::keyboard_enter const &);
	virtual void process(events::keyboard_leave const &);

	// virtuals
	SGE_SYMBOL virtual ~widget();

	SGE_SYMBOL rect const relative_area() const;
	SGE_SYMBOL rect const absolute_area() const;

	void set_size_raw(dim const &d);
	void set_pos_raw(point const &p);

	private:
	widget *const parent_;
	manager &manager_;

	point pos_;
	dim size_;
	size_policy_t size_policy_;
	keyboard_focus::type keyboard_focus_;
	mutable image buffer_;
	child_container children_;
	layout_auto_ptr layout_;
};
}
}

#endif
