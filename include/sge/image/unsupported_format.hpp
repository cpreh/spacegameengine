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


#ifndef SGE_IMAGE_UNSUPPORTED_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_UNSUPPORTED_FORMAT_HPP_INCLUDED

#include <sge/image/file_exception.hpp>
#include <sge/image/optional_path.hpp>
#include <sge/image/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/string.hpp>

namespace sge
{
namespace image
{

class SGE_CLASS_SYMBOL unsupported_format
:
	public file_exception
{
public:
	SGE_IMAGE_SYMBOL
	unsupported_format(
		optional_path const &,
		fcppt::string const &
	);
};

}
}

#endif
