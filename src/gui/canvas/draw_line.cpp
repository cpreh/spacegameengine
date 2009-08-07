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


#include <sge/gui/canvas/object.hpp>
#include <sge/gui/unit.hpp>
#include <sge/gui/exception.hpp>
#include <sge/math/signum.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/vector/output.hpp>
#include <sge/math/rect/basic_impl.hpp>
#include <sge/math/rect/contains_point.hpp>
#include <sge/math/rect/output.hpp>
#include <sge/text.hpp>
#include <sge/lexical_cast.hpp>
#include <boost/bind.hpp>
#include <algorithm>
#include <cmath>
#include <cstdlib>

namespace
{
template<
	typename T,
	typename N,
	typename S,
	typename F
>
sge::math::vector::basic<T, N, S> const
apply(
	sge::math::vector::basic<T, N, S> const &v,
	F f)
{
	sge::math::vector::basic<T, N, S> newone = v;
	std::transform(newone.begin(),newone.end(),newone.begin(),f);
	return newone;
}
}

void sge::gui::canvas::object::draw_line(
	point const &a,
	point const &b,
	color const color_,
	line_type::type const type)
{
	if (!contains_point(area(),a) || !contains_point(area(),b))
		throw exception(
			SGE_TEXT("tried to draw line from ")+
			sge::lexical_cast<sge::string>(a)+
			SGE_TEXT(" to ")+
			sge::lexical_cast<sge::string>(b)+
			SGE_TEXT(" in ")+
			sge::lexical_cast<sge::string>(area()));
	
	// increment in each direction, is also diagonal step
 	point const dd = apply(b-a,boost::bind(&math::signum<unit>,_1));
	// absolute distance between the points
	point const d = apply(b-a,boost::bind(static_cast<unit (*)(unit)>(std::abs),_1));
	// parallel step
	point const pd = d.x() > d.y() 
		? point(dd.x(),static_cast<unit>(0)) : point(static_cast<unit>(0),dd.y());
	// error values
	unit const es = std::min(d.x(),d.y()),el = std::max(d.x(),d.y());

	// current pixel position
	point pos = a;

	// set first pixel
	draw_pixel(pos,color_);

	unsigned count = 0;
 
	// t counts the pixels
	for(unit t = static_cast<unit>(0),err = static_cast<unit>(el/2-es); 
	    t < el; 
	    t += 1,err -= es) 
	{
		if(err < static_cast<unit>(0))
			// make error term positive again, then do diagonal step
			err += el, pos += dd;
		else
			// parallel step
			pos += pd;

		switch (type)
		{
			case line_type::solid:
				draw_pixel(pos,color_);
			break;
			case line_type::dashed:
				if ((count++) % 2 == 0)
					draw_pixel(pos,color_);
			break;
		}

	}
}
