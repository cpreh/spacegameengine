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


#ifndef SGE_LOG_LOGGER_HPP_INCLUDED
#define SGE_LOG_LOGGER_HPP_INCLUDED

#include <sge/log/level.hpp>
#include <sge/log/level_stream.hpp>
#include <sge/log/format/formatter_fwd.hpp>
#include <sge/ostream.hpp>
#include <sge/string.hpp>
#include <sge/export.hpp>
#include <sge/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace sge
{
namespace log
{

class temporary_output;

class logger {
	SGE_NONCOPYABLE(logger)
public:
	SGE_SYMBOL logger(
		ostream &sink,
		format::const_formatter_ptr formatter,
		bool enabled ,
		level::type);

	SGE_SYMBOL logger(
		ostream &sink,
		string const &prefix,
		bool enabled,
		level::type);

	SGE_SYMBOL logger(
		logger &parent,
		string const &prefix,
		bool enabled);

	SGE_SYMBOL ~logger();

	SGE_SYMBOL void
	log(
		level::type,
		temporary_output const &);
	
	SGE_SYMBOL level_stream &
	level_sink(
		level::type);
	
	SGE_SYMBOL level_stream const &
	level_sink(
		level::type) const;
	
	SGE_SYMBOL void
	activate(
		level::type);
	
	SGE_SYMBOL void
	deactivate(
		level::type);

	SGE_SYMBOL void
	activate_hierarchy(
		level::type);

	SGE_SYMBOL void
	deactivate_hierarchy(
		level::type);

	SGE_SYMBOL bool
	activated(
		level::type) const;
	
	SGE_SYMBOL void
	enable(
		bool);

	SGE_SYMBOL bool
	enabled() const;

	SGE_SYMBOL ostream &
	sink() const;

	SGE_SYMBOL format::const_formatter_ptr const
	formatter() const;
private:
	void init_levels(
		level::type);
	void init_level(
		level::type);
	void inherit_levels(
		logger &parent,
		level::type);
	void set_hierarchy(
		level::type,
		void (logger::*)(level::type));

	ostream                     &sink_;
	format::const_formatter_ptr formatter_;

	typedef boost::ptr_vector<
		level_stream
	> level_vector;

	bool                        enabled_;
	level_vector                level_streams;
};

}
}

#endif
