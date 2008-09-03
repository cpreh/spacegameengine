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


#ifndef SGE_LOG_LEVEL_STREAM_HPP_INCLUDED
#define SGE_LOG_LEVEL_STREAM_HPP_INCLUDED

#include "../ostream.hpp"
#include "../export.hpp"
#include "format/formatter.hpp"

namespace sge
{
namespace log
{

class temporary_output;

class level_stream {
	friend class logger;
	explicit level_stream(
		ostream &,
		format::const_formatter_ptr);
public:
	SGE_SYMBOL void enable();
	SGE_SYMBOL void disable();
	SGE_SYMBOL bool enabled() const;
	SGE_SYMBOL void log(
		temporary_output const &);
	SGE_SYMBOL void formatter(
		format::const_formatter_ptr);
	SGE_SYMBOL format::const_formatter_ptr const
	formatter() const;
private:
	ostream                     &dest_;
	format::const_formatter_ptr formatter_;
	bool                        enabled_;
};

}
}

#endif
