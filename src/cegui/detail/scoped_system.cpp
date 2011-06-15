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


#include <sge/cegui/detail/scoped_system.hpp>
#include <sge/cegui/detail/renderer.hpp>
#include <sge/cegui/detail/image_codec.hpp>
#include <sge/cegui/detail/resource_provider.hpp>
#include <CEGUISystem.h>

sge::cegui::detail::scoped_system::scoped_system(
	renderer &_renderer,
	image_codec &_image_codec,
	resource_provider &_resource_provider)
{
	CEGUI::System::create(
		_renderer,
		// Resource provider
		&_resource_provider,
		// XML parser
		0,
		&_image_codec,
		// Script module,
		0,
		// config file
		"",
		// log file
		"CEGUI.log");
}

sge::cegui::detail::scoped_system::~scoped_system()
{
	CEGUI::System::destroy();
}
