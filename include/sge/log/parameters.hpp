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
#include <sge/log/object_fwd.hpp>
#include <sge/log/format/object_fwd.hpp>
#include <sge/ostream.hpp>

namespace sge
{
namespace log
{

class parameters {
public:
	parameters const
	sink(
		ostream &
	) const;

	parameters const
	parent(
		object const &
	);

	parameters const
	context(
		log::context &
	);

	parameters const
	prefix(
		string const &
	);

	parameters const
	enabled(
		bool
	) const;

	parameters const
	formatter(
		format::const_object_ptr
	);

	object const *
	parent() const;

	ostream *
	sink() const;

	bool
	enabled() const;

	format::const_object_ptr const
	formatter() const;
private:
	object const *parent_;
	
	ostream *sink_;

	bool enabled_;

	format::const_object_ptr formatter_;
};

}
}

#endif
