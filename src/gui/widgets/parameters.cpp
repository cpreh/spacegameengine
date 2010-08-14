/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/gui/widgets/parameters.hpp>

sge::gui::widgets::parameters::parameters()
:
	pos_(),
	size_(),
	z_(static_cast<depth_type>(0)),
	size_policy_(sge::gui::size_policy::default_policy),
	keyboard_focus_(keyboard_focus::ignore),
	activation_(activation_state::active)
{
}

sge::gui::widgets::parameters &
sge::gui::widgets::parameters::pos(
	point const &_pos)
{
	pos_ = _pos;
	return *this;
}

sge::gui::widgets::parameters &
sge::gui::widgets::parameters::size(
	dim const &_size)
{
	size_ = _size;
	return *this;
}

sge::gui::widgets::parameters &
sge::gui::widgets::parameters::size_policy(
	sge::gui::size_policy const &_size_policy)
{
	size_policy_ = _size_policy;
	return *this;
}

sge::gui::widgets::parameters &
sge::gui::widgets::parameters::keyboard_focus(
	keyboard_focus::type const &_keyboard_focus)
{
	keyboard_focus_ = _keyboard_focus;
	return *this;
}

sge::gui::widgets::parameters &
sge::gui::widgets::parameters::layout(
	layouts::auto_ptr _layout)
{
	layout_ = _layout;
	return *this;
}

sge::gui::widgets::parameters &
sge::gui::widgets::parameters::activation(
	activation_state::type const _activation)
{
	activation_ = _activation;
	return *this;
}

sge::gui::widgets::optional_point const &
sge::gui::widgets::parameters::pos() const
{
	return pos_;
}

sge::gui::widgets::optional_dim const &
sge::gui::widgets::parameters::size() const
{
	return size_;
}

sge::gui::depth_type
sge::gui::widgets::parameters::z() const
{
	return z_;
}

sge::gui::size_policy const &
sge::gui::widgets::parameters::size_policy() const
{
	return size_policy_;
}

sge::gui::keyboard_focus::type const &
sge::gui::widgets::parameters::keyboard_focus() const
{
	return keyboard_focus_;
}

sge::gui::layouts::auto_ptr
sge::gui::widgets::parameters::layout() const
{
	return layout_;
}

sge::gui::activation_state::type
sge::gui::widgets::parameters::activation() const
{
	return activation_;
}
