/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/src/cegui/image_codec.hpp>
#include <sge/src/cegui/renderer.hpp>
#include <sge/src/cegui/resource_provider.hpp>
#include <sge/src/cegui/scoped_system.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/System.h>
#include <fcppt/config/external_end.hpp>


sge::cegui::scoped_system::scoped_system(
	sge::cegui::renderer &_renderer,
	sge::cegui::image_codec &_image_codec,
	sge::cegui::resource_provider &_resource_provider
)
{
	CEGUI::System::create(
		_renderer,
		// Resource provider
		&_resource_provider,
		// XML parser
		nullptr,
		&_image_codec,
		// Script module,
		nullptr,
		// config file
		"",
		// log file
		"CEGUI.log"
	);
}

sge::cegui::scoped_system::~scoped_system()
{
	CEGUI::System::destroy();
}
