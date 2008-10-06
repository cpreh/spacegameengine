/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/caps.hpp>

sge::renderer::caps::caps(
	adapter_type const adapter_number,
	string const &driver_name,
	string const &description,
	unsigned const max_tex_size,
	unsigned const max_anisotropy_level)
: adapter_number(adapter_number),
  driver_name(driver_name),
  description(description),
  max_tex_size(max_tex_size),
  max_anisotropy_level(max_anisotropy_level)
{}
