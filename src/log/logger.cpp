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
#include <sge/log/level_field.hpp>
#include <sge/log/format/default_level.hpp>
#include <sge/log/format/create_chain.hpp>
#include <sge/log/format/create_prefix.hpp>
#include <sge/foreach_enumerator.hpp>
#include <boost/bind.hpp>

sge::log::logger::logger(
	ostream &sink_,
	format::const_formatter_ptr const formatter_,
	bool const active)
:
	sink_(sink_),
	formatter_(formatter_),
	active(active)
{
	init_levels();
}

sge::log::logger::logger(
	ostream &sink_,
	string const &prefix,
	bool const active)
:
	sink_(sink_),
	formatter_(
  		format::create_prefix(
			prefix)),
	active(active)
{
	init_levels();
}

sge::log::logger::logger(
	logger &parent,
	string const &prefix,
	bool const active)
:
	sink_(parent.sink()),
	formatter_(
		format::create_chain(
			parent.formatter(),
 	 		format::create_prefix(
				prefix))),
	active(active)
{
	foreach_enumerator<level_field>(
		boost::bind(
			&logger::inherit_levels, this, boost::ref(parent), _1));
}

sge::log::logger::~logger()
{}

void sge::log::logger::log(
	level::type const level_,
	temporary_output const &helper)
{
	if (!active || !enabled(level_))
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
		&logger::activate);
}

void sge::log::logger::deactivate_hierarchy(
	level::type const level_)
{
	set_hierarchy(
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

sge::log::format::const_formatter_ptr const
sge::log::logger::formatter() const
{
	return formatter_;
}

void sge::log::logger::init_levels()
{
	foreach_enumerator<level_field>(
		boost::bind(
			&logger::init_level, this, _1));
}

void sge::log::logger::init_level(
	level::type const level_)
{
	level_streams.push_back(
		new level_stream(
			sink(),
			format::default_level(
				level_)));
}

void sge::log::logger::inherit_levels(
	logger &parent,
	level::type const level_)
{
	level_streams.push_back(
		new level_stream(
			parent.level_sink(
				level_)));
}

void sge::log::logger::set_hierarchy(
	level::type const level_,
	void (logger::*fun)(level::type))
{
	for(unsigned i = level_; i < level::size; ++i)
		(this->*fun)(
			static_cast<level::type>(
				i));
}
