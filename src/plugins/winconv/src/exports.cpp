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
#include <sge/charconv/system_fwd.hpp>
#include <sge/plugin/capabilities.hpp>
#include <sge/plugin/info.hpp>
#include <fcppt/export_symbol.hpp>
#include <fcppt/text.hpp>

extern "C"
{

FCPPT_EXPORT_SYMBOL void
plugin_version_info(
	sge::plugin::info *
);

FCPPT_EXPORT_SYMBOL sge::charconv::system *
create_charconv_system();

FCPPT_EXPORT_SYMBOL void
plugin_version_info(
	sge::plugin::info *const _info
)
{
	if(
		!_info
	)
		return;

	_info->name = FCPPT_TEXT("winconv");
	_info->description = FCPPT_TEXT("Does wchar_t (utf16) to utf-32 conversions on Windows.");
	_info->plugin_version = 0x1;
	_info->min_core_version = 0x1;
	_info->type = sge::plugin::capabilities::char_conv;
}

FCPPT_EXPORT_SYMBOL sge::charconv::system *
create_charconv_system()
{
	return new sge::winconv::system();
}

}
