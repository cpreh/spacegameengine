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


#include <sge/log/level_stream.hpp>
#include <sge/log/temporary_output.hpp>
#include <sge/log/format/create_chain.hpp>
#include <sge/log/format/formatter.hpp>

sge::log::level_stream::level_stream(
	ostream &dest_,
	format::const_formatter_ptr const formatter_)
:
	dest_(dest_),
	formatter_(formatter_),
	enabled_(false)
{}

sge::log::level_stream::~level_stream()
{}

void sge::log::level_stream::enable()
{
	enabled_ = true;
}

void sge::log::level_stream::disable()
{
	enabled_ = false;
}

bool sge::log::level_stream::enabled() const
{
	return enabled_;
}

void sge::log::level_stream::log(
	temporary_output const &output,
	format::const_formatter_ptr const additional_formatter)
{
	if(!enabled())
		return;
	
	dest_ << format::create_chain(
		additional_formatter,
		formatter())->format(output.result());
	dest_.flush();
}

void sge::log::level_stream::formatter(
	format::const_formatter_ptr const new_formatter)
{
	formatter_ = new_formatter;
}

sge::log::format::const_formatter_ptr const
sge::log::level_stream::formatter() const
{
	return formatter_;
}
