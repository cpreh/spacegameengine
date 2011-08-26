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


#include "shader.hpp"
#include "endian.hpp"
#include "max_qpath.hpp"
#include "read_string.hpp"
#include "s32.hpp"
#include <fcppt/io/read.hpp>
#include <iosfwd>

sge::model::md3::shader::shader(
	std::istream &_stream
)
:
	name_(
		md3::read_string<
			md3::max_qpath::value
		>(
			_stream
		)
	),
	shader_index_(
		fcppt::io::read<
			md3::s32
		>(
			_stream,
			md3::endian()
		)
	)
{
}
