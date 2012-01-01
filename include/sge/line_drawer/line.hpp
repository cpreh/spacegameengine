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


#ifndef SGE_LINE_DRAWER_LINE_HPP_INCLUDED
#define SGE_LINE_DRAWER_LINE_HPP_INCLUDED

#include <sge/image/colors.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/line_drawer/color.hpp>
#include <sge/line_drawer/color_format.hpp>
#include <sge/line_drawer/symbol.hpp>
#include <sge/renderer/vector3.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/variant/object.hpp>


namespace sge
{
namespace line_drawer
{
class line
{
public:
	SGE_LINE_DRAWER_SYMBOL explicit
	line(
		sge::renderer::vector3 const &,
		sge::renderer::vector3 const &,
		sge::image::color::any::object const & = sge::image::colors::white(),
		sge::image::color::any::object const & = sge::image::colors::white());

	SGE_LINE_DRAWER_SYMBOL sge::renderer::vector3 const &
	begin() const;

	SGE_LINE_DRAWER_SYMBOL sge::renderer::vector3 const &
	end() const;

	SGE_LINE_DRAWER_SYMBOL color const &
	begin_color() const;

	SGE_LINE_DRAWER_SYMBOL color const &
	end_color() const;
private:
	sge::renderer::vector3 begin_,end_;
	color begin_color_,end_color_;
};
}
}

#endif
