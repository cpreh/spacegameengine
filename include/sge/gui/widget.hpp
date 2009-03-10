#ifndef SGE_GUI_WIDGET_HPP_INCLUDED
#define SGE_GUI_WIDGET_HPP_INCLUDED

#include <sge/gui/events/fwd.hpp>
#include <sge/gui/keyboard_focus.hpp>
#include <sge/gui/activation_state.hpp>
#include <sge/gui/key_handling.hpp>
#include <sge/gui/types.hpp>
#include <sge/gui/layout_fwd.hpp>
#include <sge/gui/manager_fwd.hpp>
#include <sge/gui/size_policy.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/renderer/image.hpp>
#include <sge/noncopyable.hpp>
#include <sge/export.hpp>

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/function.hpp>

namespace sge
{
namespace gui
{
class SGE_CLASS_SYMBOL widget
{
	SGE_NONCOPYABLE(widget)
	public:
	// FIXME: rename this
	typedef sge::gui::size_policy size_policy_t;
	typedef boost::ptr_vector<widget,boost::view_clone_allocator> child_container;

	class parent_data
	{
		widget *const widget_;
		manager &manager_;

		public:
		SGE_SYMBOL parent_data(widget &);
		SGE_SYMBOL parent_data(manager &);

		widget *parent_widget() const { return widget_; }
		manager &parent_manager() const { return manager_; }
	};

	class parameters
	{
		public:
		explicit parameters(
			point const &_pos = point::null(),
			dim const &_size = dim::null(),
			layout_auto_ptr const _layout = layout_auto_ptr(),
			size_policy_t const &_size_policy = size_policy_t::default_policy,
			keyboard_focus::type const &_keyboard_focus = keyboard_focus::ignore,
			activation_state::type const _activation = activation_state::active);

		parameters &pos(point const &);
		parameters &size(dim const &);
		parameters &size_policy(size_policy_t const &);
		parameters &keyboard_focus(keyboard_focus::type const &);
		parameters &layout(layout_auto_ptr);
		parameters &activation_state(activation_state::type);

		point const &pos() const;
		dim const &size() const;
		size_policy_t const &size_policy() const;
		keyboard_focus::type const &keyboard_focus() const;
		layout_auto_ptr layout() const;
		activation_state::type activation() const;
		private:
		point pos_;
		dim size_;
		size_policy_t size_policy_;
		keyboard_focus::type keyboard_focus_;
		layout_auto_ptr layout_;
		activation_state::type activation_;
	};

	SGE_SYMBOL explicit widget(
		parent_data const &,
		parameters const &);

	SGE_SYMBOL point const screen_pos() const;
	SGE_SYMBOL point const absolute_pos() const;
	SGE_SYMBOL point const relative_pos() const;
	SGE_SYMBOL void relative_pos(point const &);
	SGE_SYMBOL dim const size() const;
	SGE_SYMBOL void size(dim const &);
	SGE_SYMBOL image &buffer() const;

	// parent stuff
	SGE_SYMBOL manager &parent_manager();
	SGE_SYMBOL manager const &parent_manager() const;
	
	SGE_SYMBOL widget *parent_widget();
	SGE_SYMBOL widget const *parent_widget() const;

	SGE_SYMBOL widget &oldest_parent();
	SGE_SYMBOL widget const &oldest_parent() const;

	SGE_SYMBOL size_policy_t const &size_policy() const;
	SGE_SYMBOL void size_policy(size_policy_t const &s);

	SGE_SYMBOL gui::keyboard_focus::type keyboard_focus() const;
	SGE_SYMBOL void keyboard_focus(keyboard_focus::type);

	SGE_SYMBOL child_container &children();
	SGE_SYMBOL child_container const &children() const;

	SGE_SYMBOL void add_child(widget &);
	SGE_SYMBOL void remove_child(widget &);

	SGE_SYMBOL void activation(activation_state::type);
	SGE_SYMBOL activation_state::type activation() const;

	SGE_SYMBOL void layout(layout_auto_ptr);

	SGE_SYMBOL layout_ptr layout();
	SGE_SYMBOL const_layout_ptr layout() const;

	SGE_SYMBOL bool has_child(widget const &) const;

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

	SGE_SYMBOL rect const absolute_area() const;
	SGE_SYMBOL rect const screen_area() const;

	private:
	friend class layout;
	void set_size_raw(dim const &d);
	void set_pos_raw(point const &p);

	widget *const parent_;
	manager &manager_;

	point pos_;
	dim size_;
	size_policy_t size_policy_;
	keyboard_focus::type keyboard_focus_;
	mutable image buffer_;
	child_container children_;
	layout_auto_ptr layout_;
	activation_state::type activation_;
};
}
}

#endif
