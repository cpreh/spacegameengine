/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/cegui/toolbox/scoped_layout.hpp>
#include <sge/cegui/to_cegui_string.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <CEGUIWindowManager.h>
#include <CEGUISystem.h>

sge::cegui::toolbox::scoped_layout::scoped_layout(
	fcppt::filesystem::path const &_path,
	sge::charconv::system &_charconv_system)
:
	window_(
		CEGUI::WindowManager::getSingleton().loadWindowLayout( 
			sge::cegui::to_cegui_string(
				fcppt::filesystem::path_to_string(
					_path),
				_charconv_system)))
{
}

sge::cegui::toolbox::scoped_layout::~scoped_layout()
{
	CEGUI::WindowManager::getSingleton().destroyWindow(
		window_);
}

CEGUI::Window &
sge::cegui::toolbox::scoped_layout::window() const
{
	return *window_;
}
