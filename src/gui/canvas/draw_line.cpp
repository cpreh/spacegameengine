/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <fcppt/math/signum.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/box/contains_point.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/lexical_cast.hpp>
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
fcppt::math::vector::basic<T, N, S> const
apply(
	fcppt::math::vector::basic<T, N, S> const &v,
	F f)
{
	fcppt::math::vector::basic<T, N, S> newone = v;
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
			FCPPT_TEXT("tried to draw line from ")+
			fcppt::lexical_cast<fcppt::string>(a)+
			FCPPT_TEXT(" to ")+
			fcppt::lexical_cast<fcppt::string>(b)+
			FCPPT_TEXT(" in ")+
			fcppt::lexical_cast<fcppt::string>(area()));

	// increment in each direction, is also diagonal step
	point const dd = apply(b-a,std::tr1::bind(&fcppt::math::signum<unit>,std::tr1::placeholders::_1));
	// absolute distance between the points
	point const d = apply(b-a,std::tr1::bind(static_cast<unit (*)(unit)>(std::abs),std::tr1::placeholders::_1));
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
