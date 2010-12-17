/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_LIBPNG_WRITE_CONTEXT_HPP_INCLUDED
#define SGE_LIBPNG_WRITE_CONTEXT_HPP_INCLUDED

#include "write_ptr.hpp"
#include "context_base.hpp"
#include "byte_vector.hpp"
#include <sge/image/color/format.hpp>
#include <sge/image2d/dim.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/io/cofstream.hpp>
#include <png.h>

namespace sge
{
namespace libpng
{
class write_context
:
	public context_base
{
public:
	write_context(
		fcppt::filesystem::path const &,
		image2d::dim const &,
		byte_vector &,
		image::color::format::type);
private:
	fcppt::io::cofstream file_;
	byte_vector &bytes_;
	image::color::format::type const format_;
	write_ptr const write_ptr_;

	static void handle_write(
		png_structp,
		png_bytep,
		png_size_t);
	void handle_write_impl(
		png_bytep,
		png_size_t);
	static void handle_flush(
		png_structp);
	void handle_flush_impl();

};
}
}

#endif
