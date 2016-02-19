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


#ifndef SGE_GUI_IMPL_DRAW_IMAGE_HPP_INCLUDED
#define SGE_GUI_IMPL_DRAW_IMAGE_HPP_INCLUDED

#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/texture/part_fwd.hpp>


namespace sge
{
namespace gui
{
namespace impl
{

void
draw_image(
	sge::renderer::device::ffp &,
	sge::renderer::context::ffp &,
	sge::texture::part const &,
	sge::rucksack::vector
);

}
}
}

#endif
