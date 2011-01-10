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


#include "unlimited_text_size.hpp"
#include <sge/gui/dim.hpp>
#include <sge/font/dim.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/text/size.hpp>
#include <sge/font/text/flags_none.hpp>
#include <sge/font/text/part.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <limits>

sge::gui::dim const
sge::gui::utility::unlimited_text_size(
	font::metrics_ptr const f,
	sge::font::text::string const &t
)
{
	return fcppt::math::dim::structure_cast<dim>(
		font::text::size(
			f,
			t,
			font::dim(
				std::numeric_limits<font::unit>::max(),
				std::numeric_limits<font::unit>::max()
			),
			sge::font::text::flags::none
		).size()
	);
}
