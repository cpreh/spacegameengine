#include <sge/gui/canvas.hpp>
#include <sge/math/signum.hpp>
#include <boost/bind.hpp>
#include <algorithm>
#include <cmath>

namespace
{
template<class T,std::size_t n,class F>
sge::math::vector<T,n> const apply(
	sge::math::vector<T,n> const &v,
	F f)
{
	sge::math::vector<T,n> newone = v;
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
	for(unit t = static_cast<unit>(0),
		err = static_cast<unit>(el/2-es); t < el; t += 1,err -= es) 
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
