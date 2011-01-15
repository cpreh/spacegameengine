/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_PROCESS_OUTPUT_HPP_INCLUDED
#define SGE_PROCESS_OUTPUT_HPP_INCLUDED

#include <sge/process/symbol.hpp>
#include <sge/process/exit_code.hpp>
#include <fcppt/string.hpp>

namespace sge
{
namespace process
{
class output
{
public:
	SGE_PROCESS_SYMBOL explicit
	output(
		fcppt::string const &out,
		fcppt::string const &err,
		sge::process::exit_code);

	SGE_PROCESS_SYMBOL fcppt::string const &
	output_stream() const;

	SGE_PROCESS_SYMBOL fcppt::string const &
	error_stream() const;

	SGE_PROCESS_SYMBOL sge::process::exit_code
	exit_code() const;
private:
	fcppt::string output_stream_,error_stream_;
	sge::process::exit_code exit_code_;
};
}
}

#endif
