/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_LIBPNG_LOAD_CONTEXT_HPP_INCLUDED
#define SGE_LIBPNG_LOAD_CONTEXT_HPP_INCLUDED

#include <sge/image/optional_path.hpp>
#include <sge/libpng/png.hpp>
#include <sge/libpng/read_ptr_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace libpng
{

class load_context
{
	FCPPT_NONCOPYABLE(
		load_context
	);
public:
	load_context(
		std::istream &,
		sge::image::optional_path const &,
		sge::libpng::read_ptr const &
	);

	~load_context();
private:
	std::istream &stream_;

	sge::image::optional_path const path_;

	static
	void
	handle_read(
		png_structp,
		png_bytep data,
		png_size_t length
	);

	void
	handle_read_impl(
		png_bytep data,
		png_size_t length
	);
};

}
}

#endif
