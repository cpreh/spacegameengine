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


#ifndef SGE_LIBPNG_FILE_REP_HPP_INCLUDED
#define SGE_LIBPNG_FILE_REP_HPP_INCLUDED

#include <sge/image2d/dim.hpp>
#include <sge/libpng/byte_vector.hpp>
#include <sge/libpng/file_rep_fwd.hpp>
#include <sge/libpng/format.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace libpng
{

class file_rep
{
	FCPPT_NONCOPYABLE(
		file_rep
	);
public:
	file_rep(
		sge::image2d::dim,
		sge::libpng::format,
		sge::libpng::byte_vector &&
	);

	file_rep(
		file_rep &&
	);

	file_rep &
	operator=(
		file_rep &&
	);

	~file_rep();

	sge::image2d::dim
	size() const;

	sge::libpng::format
	format() const;

	sge::libpng::byte_vector const &
	bytes() const;
private:
	sge::image2d::dim size_;

	sge::libpng::format format_;

	sge::libpng::byte_vector bytes_;
};

}
}

#endif
