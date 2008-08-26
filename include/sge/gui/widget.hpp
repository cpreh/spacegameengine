#ifndef SGE_GUI_WIDGET_HPP_INCLUDED
#define SGE_GUI_WIDGET_HPP_INCLUDED

#include "events/fwd.hpp"
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
	class parent_data
	{
		widgets::container *const widget_;
		manager &manager_;

		public:
		SGE_SYMBOL explicit parent_data(widgets::container &);
		SGE_SYMBOL explicit parent_data(manager &);

		widgets::container *parent_widget() const { return widget_; }
		manager &parent_manager() { return manager_; }
	};

	SGE_SYMBOL widget(
		parent_data,
		size_policy const & = size_policy::default_policy,
		point const &pos = point(),
		dim const &size = dim());

	// getters and setters go here
	point const &pos() const { return pos_; }
	dim const &size() const { return size_; }

	// parent stuff
	manager &parent_manager() { return manager_; }
	manager const &parent_manager() const { return manager_; }
	
	widgets::container *parent_widget() { return parent_; }
	widgets::container const *parent_widget() const { return parent_; }

	size_policy const &size_policy() const { return size_policy_; }
	void size_policy(size_policy const &s) { size_policy_ = s; }

	SGE_SYMBOL void size(dim const &);
	SGE_SYMBOL void pos(point const &);
	SGE_SYMBOL void compile();
	SGE_SYMBOL bool is_container() const;

	// pure virtuals
	virtual dim const size_hint() const = 0;
	virtual void process(events::invalid_area const &) {};
	virtual void process(events::mouse_enter const &) {};
	virtual void process(events::mouse_leave const &) {};
	virtual void process(events::mouse_move const &) {};
	virtual void process(events::mouse_click const &) {};

	// virtuals
	SGE_SYMBOL virtual ~widget();

	SGE_SYMBOL rect const relative_area() const;
	SGE_SYMBOL rect const absolute_area() const;

	void set_size_raw(dim const &d) { size_ = d; }
	void set_pos_raw(point const &p) { pos_ = p; }

	protected:
	virtual void do_size(dim const &) = 0;
	virtual void do_compile() = 0;
	virtual void do_pos(point const &) = 0;
	virtual widget *do_recalculate_focus(point const &) { return this; }

	private:
	// parent data
	widgets::container *const parent_;
	manager &manager_;

	point pos_;
	dim size_;
	size_policy size_policy_;

	widget *recalculate_focus(point const &mouse_click);

	// friend functions
	friend class layout;
	friend class manager;
	friend class widgets::container;
};
}
}

#endif
