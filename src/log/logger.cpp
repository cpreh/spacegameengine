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



#include <sge/log/logger.hpp>
#include <sge/log/format/default_level.hpp>
#include <sge/log/format/create_chain.hpp>
#include <sge/log/format/create_prefix.hpp>
#include <sge/make_auto_ptr.hpp>
#include <sge/foreach_enumerator.hpp>
#include <boost/tr1/functional.hpp>
#include <boost/bind.hpp>

sge::log::logger::logger(
	ostream &sink_,
	format::const_formatter_ptr const formatter_,
	bool const enabled_,
	level::type const level_)
:
	sink_(sink_),
	formatter_(formatter_),
	enabled_(enabled_),
	level_streams()
{
	init_levels(
		level_
	);
}

sge::log::logger::logger(
	ostream &sink_,
	string const &prefix,
	bool const enabled_,
	level::type const level_)
:
	sink_(sink_),
	formatter_(
  		format::create_prefix(
			prefix
		)
	),
	enabled_(enabled_),
	level_streams()
{
	init_levels(
		level_
	);
}

sge::log::logger::logger(
	logger &parent,
	string const &prefix,
	bool const enabled_)
:
	sink_(parent.sink()),
	formatter_(
		format::create_chain(
			parent.formatter(),
 	 		format::create_prefix(
				prefix
			)
		)
	),
	enabled_(enabled_),
	level_streams()
{
	SGE_FOREACH_ENUMERATOR(level_, level)
	{
		auto_ptr<
			level_stream
		> s(
			make_auto_ptr<
				level_stream
			>(
				parent.level_sink(
					level_
				)
			)
		);

		level_streams.push_back(
			s
		);
	}
}

sge::log::logger::~logger()
{}

void sge::log::logger::log(
	level::type const level_,
	temporary_output const &helper)
{
	if (!enabled() || !activated(level_))
		return;
	
	level_sink(level_).log(helper, formatter());
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
	return const_cast<logger &>(
		*this).level_sink(level_);
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

void sge::log::logger::activate_hierarchy(
	level::type const level_)
{
	set_hierarchy(
		level_,
		&logger::activate
	);
}

void sge::log::logger::deactivate_hierarchy(
	level::type const level_)
{
	set_hierarchy(
		level_,
		&logger::deactivate
	);
}

bool sge::log::logger::activated(
	level::type const level_) const
{
	return level_sink(level_).enabled();
}

void
sge::log::logger::enable(
	bool const b)
{
	enabled_ = b;
}

bool
sge::log::logger::enabled() const
{
	return enabled_;
}

sge::ostream &
sge::log::logger::sink() const
{
	return sink_;
}

sge::log::format::const_formatter_ptr const
sge::log::logger::formatter() const
{
	return formatter_;
}

void sge::log::logger::init_levels(
	level::type const level_)
{
	SGE_FOREACH_ENUMERATOR(i, level)
	{
		auto_ptr<
			level_stream
		> s(
			make_auto_ptr<
				level_stream
			>(
				std::tr1::ref(
					sink()
				),
				format::default_level(
					i	
				)
			)
		);

		level_streams.push_back(
			s
		);
	}

	activate_hierarchy(
		level_
	);
}

void sge::log::logger::set_hierarchy(
	level::type const level_,
	void (logger::*fun)(level::type))
{
	SGE_FOREACH_ENUMERATOR_2(i, level, level_)
		(this->*fun)(
			i
		);
}
