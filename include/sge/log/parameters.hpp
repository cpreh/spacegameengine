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
#include <sge/log/format/object_fwd.hpp>
#include <sge/ostream.hpp>
#include <sge/string.hpp>

namespace sge
{
namespace log
{

class parameters {
public:
	parameters();

	parameters 
	sink(
		ostream &
	) const;

	parameters 
	parent(
		object const &
	);

	parameters 
	context(
		log::context &
	);

	parameters 
	prefix(
		string const &
	);

	parameters 
	enabled(
		bool
	) const;

	parameters 
	level(
		log::level::type
	);

	parameters 
	formatter(
		format::const_object_ptr
	);

	ostream *
	sink() const;

	object const *
	parent() const;

	log::context *
	context() const;

	string const
	prefix() const;

	bool
	enabled() const;

	log::level::type
	level() const;

	format::const_object_ptr const
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
