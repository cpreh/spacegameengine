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


#ifndef SGE_SCENIC_RENDER_CONTEXT_FOG_PROPERTIES_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_FOG_PROPERTIES_HPP_INCLUDED

#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/render_context/fog/color.hpp>
#include <sge/scenic/render_context/fog/end.hpp>
#include <sge/scenic/render_context/fog/start.hpp>


namespace sge
{
namespace scenic
{
namespace render_context
{
namespace fog
{
class properties
{
public:
	SGE_SCENIC_DETAIL_SYMBOL
	properties(
		sge::scenic::render_context::fog::start const &,
		sge::scenic::render_context::fog::end const &,
		sge::scenic::render_context::fog::color const &);

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::fog::start const &
	start() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::fog::end const &
	end() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::fog::color const &
	color() const;
private:
	sge::scenic::render_context::fog::start start_;
	sge::scenic::render_context::fog::end end_;
	sge::scenic::render_context::fog::color color_;
};
}
}
}
}

#endif
