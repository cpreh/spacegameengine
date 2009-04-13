#ifndef SGE_GUI_WIDGET_HPP_INCLUDED
#define SGE_GUI_WIDGET_HPP_INCLUDED

#include <sge/gui/point.hpp>
#include <sge/gui/dim.hpp>
#include <sge/gui/rect.hpp>
#include <sge/gui/image.hpp>
#include <sge/gui/events/fwd.hpp>
#include <sge/gui/keyboard_focus.hpp>
#include <sge/gui/activation_state.hpp>
#include <sge/gui/key_handling.hpp>
#include <sge/gui/layout_fwd.hpp>
#include <sge/gui/manager_fwd.hpp>
#include <sge/gui/size_policy.hpp>
#include <sge/math/vector/basic_impl.hpp> // needed because of parameters, TODO: move them
#include <sge/math/dim/basic_impl.hpp>
#include <sge/renderer/image.hpp>
#include <sge/noncopyable.hpp>
#include <sge/gui/export.hpp>

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/function.hpp>
#include <boost/optional.hpp>

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
		SGE_GUI_SYMBOL parent_data(widget &);
		SGE_GUI_SYMBOL parent_data(manager &);

		widget *parent_widget() const { return widget_; }
		manager &parent_manager() const { return manager_; }
	};

	class parameters
	{
		public:
		parameters();
		SGE_GUI_SYMBOL parameters &pos(point const &);
		SGE_GUI_SYMBOL parameters &size(dim const &);
		SGE_GUI_SYMBOL parameters &size_policy(size_policy_t const &);
		SGE_GUI_SYMBOL parameters &keyboard_focus(keyboard_focus::type const &);
		SGE_GUI_SYMBOL parameters &layout(layout_auto_ptr);
		SGE_GUI_SYMBOL parameters &activation(activation_state::type);

		SGE_GUI_SYMBOL point const &pos() const;
		SGE_GUI_SYMBOL boost::optional<dim> const &size() const;
		SGE_GUI_SYMBOL size_policy_t const &size_policy() const;
		SGE_GUI_SYMBOL keyboard_focus::type const &keyboard_focus() const;
		SGE_GUI_SYMBOL layout_auto_ptr layout() const;
		SGE_GUI_SYMBOL activation_state::type activation() const;
		private:
		point pos_;
		boost::optional<dim> size_;
		size_policy_t size_policy_;
		keyboard_focus::type keyboard_focus_;
		layout_auto_ptr layout_;
		activation_state::type activation_;
	};

	SGE_GUI_SYMBOL explicit widget(
		parent_data const &,
		parameters const &);

	SGE_GUI_SYMBOL point const screen_pos() const;
	SGE_GUI_SYMBOL point const absolute_pos() const;
	SGE_GUI_SYMBOL point const relative_pos() const;
	SGE_GUI_SYMBOL void relative_pos(point const &);
	SGE_GUI_SYMBOL dim const size() const;
	SGE_GUI_SYMBOL void size(dim const &);
	SGE_GUI_SYMBOL image &buffer() const;

	// parent stuff
	SGE_GUI_SYMBOL manager &parent_manager();
	SGE_GUI_SYMBOL manager const &parent_manager() const;
	
	SGE_GUI_SYMBOL widget &parent_widget();
	SGE_GUI_SYMBOL widget const &parent_widget() const;

	SGE_GUI_SYMBOL bool has_parent() const;

	SGE_GUI_SYMBOL widget &oldest_parent();
	SGE_GUI_SYMBOL widget const &oldest_parent() const;

	SGE_GUI_SYMBOL size_policy_t const &size_policy() const;
	SGE_GUI_SYMBOL void size_policy(size_policy_t const &s);

	SGE_GUI_SYMBOL gui::keyboard_focus::type keyboard_focus() const;
	SGE_GUI_SYMBOL void keyboard_focus(keyboard_focus::type);

	SGE_GUI_SYMBOL child_container &children();
	SGE_GUI_SYMBOL child_container const &children() const;

	SGE_GUI_SYMBOL void add_child(widget &);
	SGE_GUI_SYMBOL void remove_child(widget &);

	SGE_GUI_SYMBOL void activation(activation_state::type);
	SGE_GUI_SYMBOL activation_state::type activation() const;

	SGE_GUI_SYMBOL void layout(layout_auto_ptr);

	SGE_GUI_SYMBOL layout_ptr layout();
	SGE_GUI_SYMBOL const_layout_ptr layout() const;

	SGE_GUI_SYMBOL bool has_child(widget const &) const;

	SGE_GUI_SYMBOL void compile();
	SGE_GUI_SYMBOL void invalidate(widget &);

	SGE_GUI_SYMBOL virtual dim const size_hint() const;
	SGE_GUI_SYMBOL boost::optional<point> const pos_hint() const;
	SGE_GUI_SYMBOL virtual void process(events::invalid_area const &);
	SGE_GUI_SYMBOL virtual void process(events::mouse_enter const &);
	SGE_GUI_SYMBOL virtual void process(events::mouse_leave const &);
	SGE_GUI_SYMBOL virtual void process(events::mouse_move const &);
	SGE_GUI_SYMBOL virtual void process(events::mouse_click const &);
	SGE_GUI_SYMBOL virtual key_handling::type process(events::key const &);
	SGE_GUI_SYMBOL virtual void process(events::keyboard_enter const &);
	SGE_GUI_SYMBOL virtual void process(events::keyboard_leave const &);

	// virtuals
	SGE_GUI_SYMBOL virtual ~widget();

	SGE_GUI_SYMBOL rect const absolute_area() const;
	SGE_GUI_SYMBOL rect const screen_area() const;

	private:
	friend class layout;

	void set_size_raw(
		dim const &d);
	void set_pos_raw(
		point const &p);

	widget *const parent_;
	manager &manager_;

	point pos_;
	dim size_;
	boost::optional<dim> size_hint_;
	boost::optional<point> pos_hint_;
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
