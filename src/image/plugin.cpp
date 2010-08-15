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


#include <sge/image/plugin.hpp>
#include "../plugin/instantiate_types.hpp"

sge::plugin::detail::address_name
sge::plugin::detail::traits<sge::image::loader>::plugin_loader_name()
{
	return SGE_ADDRESS_NAME("create_image_loader");
}

sge::plugin::capabilities::type
sge::plugin::detail::traits<sge::image::loader>::plugin_type()
{
	return capabilities::image_loader;
}

SGE_PLUGIN_INSTANTIATE_TYPES(sge::image::loader)
