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


#include <sge/plugin/info.hpp>

sge::plugin::info::info(
	fcppt::string const &_name,
	fcppt::string const &_description,
	plugin::version const _version,
	plugin::min_core_version const _min_core_version,
	plugin::capabilities_field const &_capabilities
)
:
	name_(_name),
	description_(_description),
	version_(_version),
	min_core_version_(_min_core_version),
	capabilities_(_capabilities)
{
}

fcppt::string const &
sge::plugin::info::name() const
{
	return name_;
}

fcppt::string const &
sge::plugin::info::description() const
{
	return description_;
}

sge::plugin::version const
sge::plugin::info::version() const
{
	return version_;
}

sge::plugin::min_core_version const
sge::plugin::info::min_core_version() const
{
	return min_core_version_;
}

sge::plugin::capabilities_field const &
sge::plugin::info::capabilities() const
{
	return capabilities_;
}
