/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/gui/main_area/base.hpp>
#include <sge/gui/main_area/viewport_adaptor.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>


sge::gui::main_area::viewport_adaptor::viewport_adaptor(
	sge::renderer::device::core &_device,
	sge::viewport::manager &_viewport_manager,
	sge::gui::widget::base &_widget
)
:
	sge::gui::main_area::base(),
	widget_(
		_widget
	),
	impl_(
		_viewport_manager,
		_device
	)
{
	impl_.child(
		_widget.layout()
	);

	impl_.relayout();
}

sge::gui::main_area::viewport_adaptor::~viewport_adaptor()
{
}

void
sge::gui::main_area::viewport_adaptor::relayout()
{
	impl_.relayout();
}

sge::gui::widget::base &
sge::gui::main_area::viewport_adaptor::widget()
{
	return
		widget_;
}
