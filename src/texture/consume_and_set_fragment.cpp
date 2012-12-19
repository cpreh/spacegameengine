/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image2d/dim.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/texture/consume_and_set_fragment.hpp>
#include <sge/texture/fragmented.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/part_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::texture::part_unique_ptr
sge::texture::consume_and_set_fragment(
	sge::texture::fragmented &_fragment,
	sge::image2d::view::const_object const &_view
)
{
	sge::texture::part_unique_ptr ret(
		_fragment.consume_fragment(
			sge::image2d::view::size(
				_view
			)
		)
	);

	ret->data(
		_view
	);

	return
		std::move(
			ret
		);
}
