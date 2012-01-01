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


#ifndef SGE_RENDERER_LIGHT_POINT_HPP_INCLUDED
#define SGE_RENDERER_LIGHT_POINT_HPP_INCLUDED

#include <sge/renderer/symbol.hpp>
#include <sge/renderer/light/attenuation.hpp>
#include <sge/renderer/light/point_fwd.hpp>
#include <sge/renderer/light/position.hpp>
#include <fcppt/math/vector/basic_impl.hpp>


namespace sge
{
namespace renderer
{
namespace light
{

class point
{
public:
	SGE_RENDERER_SYMBOL
	point(
		light::position const &,
		light::attenuation const &
	);

	SGE_RENDERER_SYMBOL
	light::position const &
	position() const;

	SGE_RENDERER_SYMBOL
	light::attenuation const &
	attenuation() const;
private:
	light::position position_;

	light::attenuation attenuation_;
};

}
}
}

#endif
