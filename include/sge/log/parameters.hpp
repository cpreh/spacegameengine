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


#ifndef SGE_LOG_PARAMETERS_HPP_INCLUDED
#define SGE_LOG_PARAMETERS_HPP_INCLUDED

#include <sge/log/parameters_fwd.hpp>
#include <sge/log/level.hpp>
#include <sge/log/object_fwd.hpp>
#include <sge/log/context_fwd.hpp>
#include <sge/log/format/object_ptr.hpp>
#include <sge/ostream.hpp>
#include <sge/string.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace log
{

class parameters {
public:
	SGE_SYMBOL parameters();

	SGE_SYMBOL parameters 
	sink(
		ostream &
	);

	SGE_SYMBOL parameters 
	parent(
		object const &
	);

	SGE_SYMBOL parameters 
	context(
		log::context &
	);

	SGE_SYMBOL parameters 
	prefix(
		string const &
	);

	SGE_SYMBOL parameters 
	enabled(
		bool
	);

	SGE_SYMBOL parameters 
	level(
		log::level::type
	);

	SGE_SYMBOL parameters 
	formatter(
		format::const_object_ptr
	);

	SGE_SYMBOL ostream *
	sink() const;

	SGE_SYMBOL object const *
	parent() const;

	SGE_SYMBOL log::context *
	context() const;

	SGE_SYMBOL string const
	prefix() const;

	SGE_SYMBOL bool
	enabled() const;

	SGE_SYMBOL log::level::type
	level() const;

	SGE_SYMBOL format::const_object_ptr const
	formatter() const;
private:
	ostream *sink_;

	object const *parent_;

	log::context *context_;

	string prefix_;
	
	bool enabled_;

	log::level::type level_;

	format::const_object_ptr formatter_;
};

}
}

#endif
