//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
