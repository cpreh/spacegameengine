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


#ifndef SGE_IMAGE_IMPL_PIXEL_OBJECT_OUTPUT_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_PIXEL_OBJECT_OUTPUT_IMPL_HPP_INCLUDED

#include <sge/image/pixel/object.hpp>
#include <sge/image/pixel/object_output.hpp>
#include <sge/image/pixel/print.hpp>
#include <fcppt/io/ostream_fwd.hpp>
#include <fcppt/variant/apply_unary.hpp>


template<
	typename Tag
>
fcppt::io::ostream &
sge::image::pixel::operator<<(
	fcppt::io::ostream &_stream,
	sge::image::pixel::object<
		Tag
	> const &_object
)
{
	return
		fcppt::variant::apply_unary(
			[
				&_stream
			](
				auto const &_value
			)
			->
			fcppt::io::ostream &
			{
				return
					_stream
					<<
					_value;
			},
			_object.get()
		);
}

#endif
