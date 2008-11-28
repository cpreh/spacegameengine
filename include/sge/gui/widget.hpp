#ifndef SGE_GUI_WIDGET_HPP_INCLUDED
#define SGE_GUI_WIDGET_HPP_INCLUDED

#include "events/fwd.hpp"
#include "keyboard_focus.hpp"
#include "types.hpp"
#include "size_policy.hpp"
#include "../export.hpp"

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>

namespace sge
{
namespace gui
{
// forward declarations
namespace widgets
{
class container;
}
class manager;

// declaration
class SGE_CLASS_SYMBOL widget : boost::noncopyable
{
	public:
	typedef sge::gui::size_policy size_policy_t;

	class parent_data
	{
		widgets::container *const widget_;
		manager &manager_;

		public:
		SGE_SYMBOL explicit parent_data(widgets::container &);
		SGE_SYMBOL explicit parent_data(manager &);

		widgets::container *parent_widget() const { return widget_; }
		manager &parent_manager() const { return manager_; }
	};

	SGE_SYMBOL explicit widget(
		parent_data,
		size_policy_t const & = size_policy_t::default_policy,
		keyboard_focus::type receives_keys = keyboard_focus::ignore);

	// getters and setters go here
	point const &pos() const;
	dim const &size() const;

	// parent stuff
	manager &parent_manager();
	manager const &parent_manager() const;
	
	widgets::container *parent_widget();
	widgets::container const *parent_widget() const;

	size_policy_t const &size_policy() const;
	void size_policy(size_policy_t const &s);

	gui::keyboard_focus::type keyboard_focus() const;
	void keyboard_focus(keyboard_focus::type);

	SGE_SYMBOL void size(dim const &);
	SGE_SYMBOL void pos(point const &);
	SGE_SYMBOL void compile();
	SGE_SYMBOL bool is_container() const;

	virtual dim const size_hint() const = 0;
	virtual void process(events::invalid_area const &);
	virtual void process(events::mouse_enter const &);
	virtual void process(events::mouse_leave const &);
	virtual void process(events::mouse_move const &);
	virtual void process(events::mouse_click const &);
	virtual void process(events::key const &);
	virtual void process(events::keyboard_enter const &);
	virtual void process(events::keyboard_leave const &);

	// virtuals
	SGE_SYMBOL virtual ~widget();

	SGE_SYMBOL rect const relative_area() const;
	SGE_SYMBOL rect const absolute_area() const;

	void set_size_raw(dim const &d);
	void set_pos_raw(point const &p);

	protected:
	virtual void do_compile();

	private:
	widgets::container *const parent_;
	manager &manager_;

	point pos_;
	dim size_,size_hint_;
	size_policy_t size_policy_;
	keyboard_focus::type keyboard_focus_;

	// friend functions
	friend class layout;
	friend class manager;
	friend class widgets::container;
};
}
}

#endif
