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


#include <sge/renderer/exception.hpp>
#include <sge/renderer/index/format_16.hpp>
#include <sge/renderer/index/format_32.hpp>
#include <sge/renderer/index/view.hpp>
#include <sge/renderer/index/any/make_view.hpp>
#include <sge/renderer/index/any/view.hpp>
#include <sge/renderer/index/dynamic/view.hpp>
#include <fcppt/text.hpp>
#include <fcppt/variant/object_impl.hpp>


sge::renderer::index::any::view const
sge::renderer::index::any::make_view(
	renderer::index::dynamic::view const &_view
)
{
	switch(
		_view.format()
	)
	{
	case index::dynamic::format::i16:
		return
			index::view<
				index::format_16
			>(
				_view.data(),
				_view.size()
			);
	case index::dynamic::format::i32:
		return
			index::view<
				index::format_32
			>(
				_view.data(),
				_view.size()
			);
	}

	throw sge::renderer::exception(
		FCPPT_TEXT("Invalid format in index::any::make_view!")
	);
}
