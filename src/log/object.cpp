/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/log/object.hpp>
#include <sge/log/parameters/all.hpp>
#include <sge/log/context.hpp>
#include <sge/log/level_stream.hpp>

sge::log::object::object(
	parameters::all const &param_
)
:
	parent_(
		param_.parent()
	),
	sink_(
		param_.sink()
	),
	auto_context_(
		param_.context_location(),
		*this
	),
	formatter_(
		param_.formatter()
	),
	enabled_(
		param_.enabled()
	),
	level_streams_(
		param_.level_streams()
	),
	enabled_levels_(
		param_.enabled_levels()
	)
{
}

sge::log::object::~object()
{}

void
sge::log::object::log(
	level::type const level_,
	temporary_output const &helper
)
{
	if(
		!enabled()
		|| !activated(level_)
	)
		return;

	level_sink(level_).log(
		helper,
		formatter()
	);
}

sge::log::level_stream &
sge::log::object::level_sink(
	level::type const level_
)
{
	return *level_streams_.at(
		level_
	);
}

sge::log::level_stream const &
sge::log::object::level_sink(
	level::type const level_
) const
{
	return *level_streams_.at(
		level_
	);
}

void
sge::log::object::activate(
	level::type const level_
)
{
	enabled_levels_[
		level_
	] = true;
}

void
sge::log::object::deactivate(
	level::type const level_
)
{
	enabled_levels_[
		level_
	] = false;
}

bool
sge::log::object::activated(
	level::type const level_
) const
{
	return
		enabled_levels_[
			level_
		];
}

void
sge::log::object::enable(
	bool const b
)
{
	enabled_ = b;
}

bool
sge::log::object::enabled() const
{
	return enabled_;
}

sge::ostream &
sge::log::object::sink() const
{
	return sink_;
}

sge::log::format::const_object_ptr const
sge::log::object::formatter() const
{
	return formatter_;
}

sge::log::context_location const
sge::log::object::context_location() const
{
	return auto_context_.location();
}

sge::log::level_stream_array const &
sge::log::object::level_streams() const
{
	return level_streams_;
}

sge::log::enabled_level_array const &
sge::log::object::enabled_levels() const
{
	return enabled_levels_;
}
