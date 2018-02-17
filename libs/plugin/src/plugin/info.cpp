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


#include <sge/plugin/capabilities_field.hpp>
#include <sge/plugin/description.hpp>
#include <sge/plugin/flags_field.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/min_core_version.hpp>
#include <sge/plugin/name.hpp>
#include <sge/plugin/version.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::plugin::info::info(
	sge::plugin::name &&_name,
	sge::plugin::description &&_description,
	sge::plugin::version const _version,
	sge::plugin::min_core_version const _min_core_version,
	sge::plugin::capabilities_field const &_capabilities,
	sge::plugin::flags_field const &_flags
)
:
	name_(
		std::move(
			_name
		)
	),
	description_(
		std::move(
			_description
		)
	),
	version_(
		_version
	),
	min_core_version_(
		_min_core_version
	),
	capabilities_(
		_capabilities
	),
	flags_(
		_flags
	)
{
}

sge::plugin::name const &
sge::plugin::info::name() const
{
	return
		name_;
}

sge::plugin::description const &
sge::plugin::info::description() const
{
	return
		description_;
}

sge::plugin::version
sge::plugin::info::version() const
{
	return
		version_;
}

sge::plugin::min_core_version
sge::plugin::info::min_core_version() const
{
	return
		min_core_version_;
}

sge::plugin::capabilities_field const &
sge::plugin::info::capabilities() const
{
	return
		capabilities_;
}

sge::plugin::flags_field const &
sge::plugin::info::flags() const
{
	return
		flags_;
}
