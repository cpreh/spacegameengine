/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../common.hpp"
#include "../target.hpp"
#include "../read_pixels.hpp"
#include "../color_convert.hpp"
#include <sge/image/view/make.hpp>
#include <sge/image/view/make_const.hpp>
#include <sge/image/view/flipped.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/optional_impl.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

sge::opengl::target::target()
{}

sge::opengl::target::~target()
{}

sge::image::view::const_object const
sge::opengl::target::lock(
	renderer::lock_rect const &dest
) const
{
	if(
		!buffer.empty()
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("renderer::target()::lock(): already locked!")
		);

	buffer.resize_uninitialized(
		dest.dimension().content() * stride()
	);

	bind_me();

	read_pixels(
		pos().x() + dest.left(),
		pos().y() + dest.top(),
		dest.dimension().w(),
		dest.dimension().h(),
		format(),
		format_type(),
		buffer.data()
	);

	return
		image::view::make_const(
			image::view::flipped(
				image::view::make(
					buffer.data(),
					dim(),
					opengl::color_convert(
						format(),
						format_type()
					),
					image::view::optional_pitch()
				)
			)
		);
}

void
sge::opengl::target::unlock() const
{
	buffer.free_memory();
}
