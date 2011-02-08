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


#include "../system.hpp"
#include <sge/charconv/system_ptr.hpp>
#include <sge/font/system_ptr.hpp>
#include <sge/plugin/library/make_interface.hpp>
#include <sge/plugin/capabilities.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/min_core_version.hpp>
#include <sge/plugin/version.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>

namespace
{

sge::plugin::info const info(
	FCPPT_TEXT("freetype"),
	FCPPT_TEXT("Provides loading of truetype fonts."),
	sge::plugin::version(0x1),
	sge::plugin::min_core_version(0x1),
	sge::plugin::capabilities::font
);

sge::font::system_ptr const
create_font_system(
	sge::charconv::system_ptr const _charconv_system
)
{
	return
		fcppt::make_shared_ptr<
			sge::freetype::system
		>(
			_charconv_system
		);
}

}

SGE_PLUGIN_LIBRARY_MAKE_INTERFACE(
	info,
	(create_font_system)
)
