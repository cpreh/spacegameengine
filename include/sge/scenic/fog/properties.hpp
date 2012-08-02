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


#ifndef SGE_SCENIC_FOG_PROPERTIES_HPP_INCLUDED
#define SGE_SCENIC_FOG_PROPERTIES_HPP_INCLUDED

#include <sge/scenic/symbol.hpp>
#include <sge/scenic/fog/color.hpp>
#include <sge/scenic/fog/end.hpp>
#include <sge/scenic/fog/start.hpp>


namespace sge
{
namespace scenic
{
namespace fog
{
class properties
{
public:
	SGE_SCENIC_SYMBOL
	properties(
		sge::scenic::fog::start const &,
		sge::scenic::fog::end const &,
		sge::scenic::fog::color const &);

	SGE_SCENIC_SYMBOL
	sge::scenic::fog::start const &
	start() const;

	SGE_SCENIC_SYMBOL
	sge::scenic::fog::end const &
	end() const;

	SGE_SCENIC_SYMBOL
	sge::scenic::fog::color const &
	color() const;
private:
	sge::scenic::fog::start start_;
	sge::scenic::fog::end end_;
	sge::scenic::fog::color color_;
};
}
}
}

#endif
