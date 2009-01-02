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
	adapter_type const adapter_,
	string const &driver_name_,
	string const &description_,
	dim_type const &max_texture_size_,
	anisotropy_type const max_anisotropy_)
:
	adapter_(adapter_),
	driver_name_(driver_name_),
	description_(description_),
	max_texture_size_(max_texture_size_),
	max_anisotropy_(max_anisotropy_)
{}

sge::renderer::adapter_type
sge::renderer::caps::adapter() const
{
	return adapter_;
}

sge::string const &
sge::renderer::caps::driver_name() const
{
	return driver_name_;
}

sge::string const &
sge::renderer::caps::description() const
{
	return description_;
}

sge::renderer::dim_type const &
sge::renderer::caps::max_texture_size() const
{
	return max_texture_size_;
}

sge::renderer::anisotropy_type
sge::renderer::caps::max_anisotropy() const
{
	return max_anisotropy_;
}
