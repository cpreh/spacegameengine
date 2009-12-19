/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_GUI_WIDGETS_BASE_HPP_INCLUDED
#define SGE_GUI_WIDGETS_BASE_HPP_INCLUDED

#include <sge/gui/widgets/parameters_fwd.hpp>
#include <sge/gui/widgets/parent_data.hpp>
#include <sge/gui/widgets/optional_point.hpp>
#include <sge/gui/widgets/optional_dim.hpp>
#include <sge/gui/point.hpp>
#include <sge/gui/depth_type.hpp>
#include <sge/gui/invalidation.hpp>
#include <sge/gui/dim.hpp>
#include <sge/gui/rect.hpp>
#include <sge/gui/image.hpp>
#include <sge/gui/events/fwd.hpp>
#include <sge/gui/keyboard_focus.hpp>
#include <sge/gui/activation_state.hpp>
#include <sge/gui/key_handling.hpp>
#include <sge/gui/layouts/fwd.hpp>
#include <sge/gui/manager_fwd.hpp>
#include <sge/gui/size_policy.hpp>
#include <sge/image/store.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <sge/noncopyable.hpp>
#include <sge/gui/export.hpp>
#include <fcppt/optional.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
class SGE_CLASS_SYMBOL base
{
	SGE_NONCOPYABLE(base)
	public:
	typedef boost::ptr_vector<
		widgets::base,
		boost::view_clone_allocator> child_container;

	/**
	 * This:
	 * -Sets the layout's connected widget (can only be set once)
	 * -Calls base::add_child on the parent widget (if any)
	 * -Calls manager::add(*this)
	 */
	SGE_GUI_SYMBOL base(
		parent_data const &,
		parameters const &);

	//! position on the screen
	SGE_GUI_SYMBOL point const screen_pos() const;
	//! position relative to the oldest parent (position on the sprite)
	SGE_GUI_SYMBOL point const absolute_pos() const;
	//! position relative to its parent (=screen_pos if the widget has no parent)
	SGE_GUI_SYMBOL point const relative_pos() const;
	//! this only sets the position immediately if it's a top level widget
	SGE_GUI_SYMBOL void pos_hint(point const &);
	SGE_GUI_SYMBOL optional_point const pos_hint() const;
	SGE_GUI_SYMBOL dim const size() const;
	SGE_GUI_SYMBOL void size_hint(dim const &);
	SGE_GUI_SYMBOL optional_dim const size_hint() const;

	SGE_GUI_SYMBOL void z(depth_type);
	SGE_GUI_SYMBOL depth_type z() const;

	SGE_GUI_SYMBOL image &buffer() const;

	SGE_GUI_SYMBOL manager &parent_manager();
	SGE_GUI_SYMBOL manager const &parent_manager() const;

	SGE_GUI_SYMBOL widgets::base &parent_widget();
	SGE_GUI_SYMBOL widgets::base const &parent_widget() const;

	SGE_GUI_SYMBOL bool has_parent() const;

	SGE_GUI_SYMBOL widgets::base &oldest_parent();
	SGE_GUI_SYMBOL widgets::base const &oldest_parent() const;

	SGE_GUI_SYMBOL sge::gui::size_policy const &size_policy() const;
	SGE_GUI_SYMBOL void size_policy(sge::gui::size_policy const &s);

	SGE_GUI_SYMBOL gui::keyboard_focus::type keyboard_focus() const;
	SGE_GUI_SYMBOL void keyboard_focus(keyboard_focus::type);

	SGE_GUI_SYMBOL child_container &children();
	SGE_GUI_SYMBOL child_container const &children() const;

	SGE_GUI_SYMBOL virtual void add_child(widgets::base &);
	SGE_GUI_SYMBOL virtual void remove_child(widgets::base &);

	SGE_GUI_SYMBOL void activation(activation_state::type);
	SGE_GUI_SYMBOL activation_state::type activation() const;

	SGE_GUI_SYMBOL void layout(layouts::auto_ptr);

	SGE_GUI_SYMBOL layouts::base &layout();
	SGE_GUI_SYMBOL layouts::base const &layout() const;

	SGE_GUI_SYMBOL bool has_child(widgets::base const &) const;

	SGE_GUI_SYMBOL rect const absolute_area() const;
	SGE_GUI_SYMBOL rect const screen_area() const;

	SGE_GUI_SYMBOL virtual void compile(invalidation::type const &);
	SGE_GUI_SYMBOL virtual void compile_static();
	SGE_GUI_SYMBOL virtual dim const optimal_size() const;
	SGE_GUI_SYMBOL void invalidate(
		widgets::base &,
		invalidation::type const &);

	SGE_GUI_SYMBOL virtual void process_invalid_area(events::invalid_area const &);
	SGE_GUI_SYMBOL virtual void process_mouse_enter(events::mouse_enter const &);
	SGE_GUI_SYMBOL virtual void process_mouse_leave(events::mouse_leave const &);
	SGE_GUI_SYMBOL virtual void process_mouse_move(events::mouse_move const &);
	SGE_GUI_SYMBOL virtual void process_mouse_click(events::mouse_click const &);
	SGE_GUI_SYMBOL virtual key_handling::type process_key(events::key const &);
	SGE_GUI_SYMBOL virtual void process_keyboard_enter(events::keyboard_enter const &);
	SGE_GUI_SYMBOL virtual void process_keyboard_leave(events::keyboard_leave const &);

	// virtuals
	SGE_GUI_SYMBOL virtual ~base();
	private:
	widgets::base *const parent_;
	manager &manager_;

	point pos_;
	optional_point pos_hint_;
	dim size_;
	optional_dim size_hint_;
	depth_type z_;
	sge::gui::size_policy size_policy_;
	keyboard_focus::type keyboard_focus_;
	mutable image buffer_;
	child_container children_;
	layouts::auto_ptr layout_;
	activation_state::type activation_;

	friend class layouts::base;
	void size(
		dim const &d);
	void pos(
		point const &p);

};
}
}
}

#endif
