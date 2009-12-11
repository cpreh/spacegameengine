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


#ifndef SGE_GUI_MANAGER_HPP_INCLUDED
#define SGE_GUI_MANAGER_HPP_INCLUDED

#include <sge/gui/detail/managers/fwd.hpp>
#include <sge/gui/timer/callback.hpp>
#include <sge/gui/timer/fwd.hpp>
#include <sge/gui/skins/base.hpp>
#include <sge/gui/widgets/fwd.hpp>
#include <sge/gui/cursor/base_ptr.hpp>
#include <sge/gui/cursor/const_base_ptr.hpp>
#include <sge/gui/sprite/object.hpp>
#include <sge/gui/export.hpp>
#include <sge/gui/rect.hpp>
#include <sge/gui/invalidation.hpp>
#include <sge/gui/point.hpp>
#include <sge/gui/depth_type.hpp>
#include <sge/gui/activation_state.hpp>
#include <sge/gui/keyboard_focus.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/texture_fwd.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/time/resolution.hpp>
#include <sge/noncopyable.hpp>
#include <sge/scoped_ptr.hpp>
#include <vector>

namespace sge
{
namespace gui
{
class manager
{
	SGE_NONCOPYABLE(manager)
	public:
	SGE_GUI_SYMBOL manager(
		renderer::device_ptr,
		input::system_ptr,
		skins::ptr,
		cursor::base_ptr);
	SGE_GUI_SYMBOL ~manager();
	SGE_GUI_SYMBOL void dirty(
		widgets::base &,
		rect const &);
	SGE_GUI_SYMBOL void invalidate(
		widgets::base &,
		invalidation::type const &);
	SGE_GUI_SYMBOL timer::object_ptr const register_timer(
		time::resolution const &,
		timer::callback);
	SGE_GUI_SYMBOL void update();
	SGE_GUI_SYMBOL void draw();
	SGE_GUI_SYMBOL sge::gui::cursor::const_base_ptr const cursor() const;
	SGE_GUI_SYMBOL skins::base &skin();
	SGE_GUI_SYMBOL skins::base const &skin() const;

	SGE_GUI_SYMBOL sge::gui::sprite::object &
	connected_sprite(
		widgets::base &
	);

	SGE_GUI_SYMBOL void request_keyboard_focus(
		widgets::base &);
	SGE_GUI_SYMBOL void z(
		widgets::base &,
		depth_type);
	private:
	friend class widgets::base;

	skins::ptr const skin_;
	cursor::base_ptr const cursor_;

	// this is just to prevent the detail dependencies
	scoped_ptr<detail::managers::mouse> mouse_;
	scoped_ptr<detail::managers::render> render_;
	scoped_ptr<detail::managers::keyboard> keyboard_;
	scoped_ptr<detail::managers::compiler> compiler_;
	scoped_ptr<detail::managers::time> timer_;

	typedef std::vector<detail::submanager*> submanager_container;
	submanager_container submanagers;

	// this is called by widget's constructor and destructor
	void add(widgets::base &);
	void remove(widgets::base &);

	void resize(
		widgets::base &,
		dim const &);
	void reposition(
		widgets::base &,
		point const &);
	void activation(
		widgets::base &,
		activation_state::type);
	void keyboard_focus(
		widgets::base &,
		keyboard_focus::type);
};
}
}

#endif
