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


#include <sge/renderer/aspect.hpp>
#include <fcppt/export_symbol.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/math/dim/basic_impl.hpp>


sge::renderer::scalar
sge::renderer::aspect(
	screen_size const &_size
)
{
	FCPPT_ASSERT_PRE(
		_size.w() != 0 && _size.h() != 0
	);

	sge::renderer::scalar const
		width(
			static_cast<
				renderer::scalar
			>(
				_size.w()
			)
		),
		height(
			static_cast<
				renderer::scalar
			>(
				_size.h()
			)
		);

	return
		width > height
		?
			width / height
		:
			height / width;
}
