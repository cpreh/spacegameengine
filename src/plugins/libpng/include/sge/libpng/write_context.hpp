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


#ifndef SGE_LIBPNG_WRITE_CONTEXT_HPP_INCLUDED
#define SGE_LIBPNG_WRITE_CONTEXT_HPP_INCLUDED

#include <sge/image/optional_path.hpp>
#include <sge/libpng/png.hpp>
#include <sge/libpng/write_ptr_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace libpng
{

class write_context
{
	FCPPT_NONCOPYABLE(
		write_context
	);
public:
	write_context(
		sge::image::optional_path const &,
		std::ostream &,
		sge::libpng::write_ptr const &
	);

	~write_context();
private:
	sge::image::optional_path const path_;

	std::ostream &stream_;

	static
	void
	handle_write(
		png_structp,
		png_bytep,
		png_size_t
	);

	void
	handle_write_impl(
		png_bytep,
		png_size_t
	);

	static
	void
	handle_flush(
		png_structp
	);

	void
	handle_flush_impl();

	static
	write_context &
	get_instance(
		png_structp
	);
};

}
}

#endif
