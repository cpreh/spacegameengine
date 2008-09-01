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


#include <sge/log/logger.hpp>
#include <sge/log/default_formatter.hpp>

sge::log::logger::logger(
	ostream &sink_)
: sink_(sink_)
{
	init_levels();
}

void sge::log::logger::log(
	level::type const level_,
	temporary_output const &helper)
{
	if(!enabled(level_))
		return;
	
	level_sink(level_).log(helper);
}

sge::log::level_stream &
sge::log::logger::level_sink(
	level::type const level_)
{
	return level_streams.at(level_);
}

sge::log::level_stream const &
sge::log::logger::level_sink(
	level::type const level_) const
{
	return const_cast<logger &>(*this).level_sink(level_);
}

void sge::log::logger::activate(
	level::type const level_)
{
	level_sink(level_).enable();
}

void sge::log::logger::deactivate(
	level::type const level_)
{
	level_sink(level_).disable();
}

void sge::log::logger::activate_hierarchie(
	level::type const level_)
{
	set_hierarchie(
		level_,
		&logger::activate);
}

void sge::log::logger::deactivate_hierarchie(
	level::type const level_)
{
	set_hierarchie(
		level_,
		&logger::deactivate);
}

bool sge::log::logger::enabled(
	level::type const level_) const
{
	return level_sink(level_).enabled();
}

sge::ostream &
sge::log::logger::sink() const
{
	return sink_;
}

void sge::log::logger::init_levels()
{
	for(unsigned i = 0; i < level::size; ++i)
		level_streams.push_back(
			new level_stream(
				sink(),
				default_formatter(
					static_cast<level::type>(
						i)
				)
			)
		);
}

void sge::log::logger::set_hierarchie(
	level::type const level_,
	void (logger::*fun)(level::type))
{
	for(unsigned i = level_; i < level::size; ++i)
		(this->*fun)(level_);
}
