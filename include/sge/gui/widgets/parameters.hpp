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


#ifndef SGE_GUI_WIDGETS_PARAMETERS_HPP_INCLUDED
#define SGE_GUI_WIDGETS_PARAMETERS_HPP_INCLUDED

#include <sge/gui/widgets/parameters_fwd.hpp>
#include <sge/gui/widgets/optional_point.hpp>
#include <sge/gui/widgets/optional_dim.hpp>
#include <sge/gui/export.hpp>
#include <sge/gui/point.hpp>
#include <sge/gui/depth_type.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <sge/gui/dim.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <sge/gui/size_policy.hpp>
#include <sge/gui/layouts/fwd.hpp>
#include <sge/gui/keyboard_focus.hpp>
#include <sge/gui/activation_state.hpp>
#include <fcppt/optional.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
class parameters
{
public:
	SGE_GUI_SYMBOL parameters();
	SGE_GUI_SYMBOL parameters &pos(point const &);
	SGE_GUI_SYMBOL parameters &size(dim const &);
	SGE_GUI_SYMBOL parameters &size_policy(sge::gui::size_policy const &);
	SGE_GUI_SYMBOL parameters &keyboard_focus(keyboard_focus::type const &);
	SGE_GUI_SYMBOL parameters &layout(layouts::auto_ptr);
	SGE_GUI_SYMBOL parameters &activation(activation_state::type);

	SGE_GUI_SYMBOL optional_point const &pos() const;
	SGE_GUI_SYMBOL optional_dim const &size() const;
	SGE_GUI_SYMBOL depth_type z() const;
	SGE_GUI_SYMBOL sge::gui::size_policy const &size_policy() const;
	SGE_GUI_SYMBOL keyboard_focus::type const &keyboard_focus() const;
	SGE_GUI_SYMBOL layouts::auto_ptr layout() const;
	SGE_GUI_SYMBOL activation_state::type activation() const;
private:
	optional_point pos_;
	optional_dim size_;
	depth_type z_;
	sge::gui::size_policy size_policy_;
	keyboard_focus::type keyboard_focus_;
	layouts::auto_ptr layout_;
	activation_state::type activation_;
};
}
}
}

#endif
