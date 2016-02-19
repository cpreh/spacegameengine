/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/font/flags_field.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/align_h/variant.hpp>


sge::font::text_parameters::text_parameters(
	sge::font::align_h::variant const &_align_h
)
:
	align_h_(
		_align_h
	),
	flags_(
		sge::font::flags_field::null()
	)
{
}

sge::font::text_parameters &
sge::font::text_parameters::flags(
	sge::font::flags_field const &_flags
)
{
	flags_ = _flags;

	return
		*this;
}

sge::font::align_h::variant const &
sge::font::text_parameters::align_h() const
{
	return
		align_h_;
}

sge::font::flags_field const &
sge::font::text_parameters::flags() const
{
	return
		flags_;
}
