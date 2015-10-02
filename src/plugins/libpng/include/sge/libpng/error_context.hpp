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


#ifndef SGE_LIBPNG_ERROR_CONTEXT_HPP_INCLUDED
#define SGE_LIBPNG_ERROR_CONTEXT_HPP_INCLUDED

#include <sge/libpng/error_context_fwd.hpp>
#include <sge/libpng/png.hpp>
#include <sge/media/optional_name.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional.hpp>


namespace sge
{
namespace libpng
{

class error_context
{
	FCPPT_NONCOPYABLE(
		error_context
	);
public:
	explicit
	error_context(
		sge::media::optional_name const &
	);

	~error_context();

	static
	void
	handle_warning(
		png_structp,
		png_const_charp
	);

	static
	void
	handle_error(
		png_structp,
		png_const_charp
	);
private:
	sge::media::optional_name const name_;

	void
	handle_warning_impl(
		png_const_charp
	);

	void
	handle_error_impl(
		png_const_charp
	);

	static
	error_context &
	get_instance(
		png_structp
	);
};

}
}

#endif
