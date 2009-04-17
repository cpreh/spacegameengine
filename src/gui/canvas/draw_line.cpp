#include <sge/gui/canvas/object.hpp>
#include <sge/gui/unit.hpp>
#include <sge/math/signum.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/vector/output.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/text.hpp>
#include <sge/lexical_cast.hpp>
#include <sge/exception.hpp>
#include <boost/bind.hpp>
#include <algorithm>
#include <cmath>

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
	if (!math::contains(area(),a) || !math::contains(area(),b))
		throw sge::exception(
			SGE_TEXT("tried to draw line from ")+
			sge::lexical_cast<sge::string>(a)+
			SGE_TEXT(" to ")+
			sge::lexical_cast<sge::string>(b)+
			SGE_TEXT(" in ")+
			sge::lexical_cast<sge::string>(area()));
	
	// increment in each direction, is also diagonal step
 	point const dd = apply(b-a,boost::bind(&math::signum<unit>,_1));
	// absolute distance between the points
	point const d = apply(b-a,boost::bind(&std::abs<unit>,_1));
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
