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


#ifndef SGE_LIBPNG_LOAD_CONTEXT_HPP_INCLUDED
#define SGE_LIBPNG_LOAD_CONTEXT_HPP_INCLUDED

#include "context_base.hpp"
#include "read_ptr.hpp"
#include "byte_vector.hpp"
#include <sge/image/color/format.hpp>
#include <sge/image/optional_path.hpp>
#include <sge/image2d/dim.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/math/dim/basic_decl.hpp>
#include <fcppt/io/cifstream.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <png.h>
#include <istream>
#include <cstddef>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace libpng
{
class load_context
:
	public context_base
{
	FCPPT_NONCOPYABLE(
		load_context
	);
public:
	explicit load_context(
		std::istream &,
		sge::image::optional_path const &);

	image2d::dim const &dim() const;
	byte_vector &bytes();
	byte_vector const &bytes() const;
	image::color::format::type format() const;
private:
	static std::size_t const header_bytes_;

	std::istream &stream_;
	fcppt::scoped_ptr<read_ptr> read_ptr_;
	image2d::dim dim_;
	byte_vector bytes_;
	image::color::format::type format_;

	bool is_png();
	static void handle_read(
		png_structp,
		png_bytep data,
		png_size_t length);
	void handle_read_impl(
		png_bytep data,
		png_size_t length);
	sge::image::color::format::type convert_format() const;
	sge::image::color::format::type convert_gray_format() const;
	sge::image::color::format::type convert_rgb_format() const;
	sge::image::color::format::type convert_rgba_format() const;
};
}
}

#endif
