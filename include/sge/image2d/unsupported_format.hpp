/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_IMAGE2D_UNSUPPORTED_FORMAT_HPP_INCLUDED
#define SGE_IMAGE2D_UNSUPPORTED_FORMAT_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/image2d/file_exception.hpp>
#include <sge/image2d/detail/symbol.hpp>
#include <sge/media/optional_path_fwd.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace image2d
{

class SGE_CORE_DETAIL_CLASS_SYMBOL unsupported_format
:
	public sge::image2d::file_exception
{
public:
	SGE_IMAGE_DETAIL_SYMBOL
	unsupported_format(
		sge::media::optional_path const &,
		fcppt::string const &
	);
};

}
}

#endif
