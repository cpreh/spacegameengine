#include "utility/font_blitter.hpp"
#include "utility/set_pixel.hpp"

#include <sge/gui/canvas.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/font_drawer_canvas.hpp>
#include <sge/renderer/fill_pixels.hpp>
#include <sge/renderer/transform_pixels.hpp>
#include <sge/renderer/make_const_image_view.hpp>

#include <sge/math/rect_impl.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/math/signum.hpp>
#include <sge/format.hpp>
#include <sge/assert.hpp>
#include <sge/iostream.hpp>

#include <boost/gil/extension/dynamic_image/algorithm.hpp>
#include <boost/gil/extension/dynamic_image/apply_operation.hpp>
#include <boost/gil/extension/dynamic_image/image_view_factory.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

#include <algorithm>

#include <cmath>
#include <cstdlib>

namespace
{
template<class T,std::size_t n,class F>
sge::math::vector<T,n> apply(sge::math::vector<T,n> const &v,F f)
{
	sge::math::vector<T,n> newone = v;
	std::transform(newone.begin(),newone.end(),newone.begin(),f);
	return newone;
}
}

namespace
{
sge::gui::logger mylogger(sge::gui::global_log(),SGE_TEXT("canvas"),false);
}

sge::gui::canvas::canvas(
	view_type const &texture_,
	rect const &widget_,
	rect const &invalid_)
:
	texture_(texture_),
	widget_(widget_),
	invalid_(invalid_),
	drawer(new font_drawer_canvas(*this))
{
}

void sge::gui::canvas::reset_font(
	font::metrics_ptr _metrics,
	color const fg)
{
	metrics = _metrics;

	// temporarily convert to canvas_drawer to set foreground and background
	font_drawer_canvas &cd = static_cast<font_drawer_canvas &>(*drawer);
	cd.fg(fg);

	font.reset(new font::font(metrics,drawer));
}

sge::gui::dim const sge::gui::canvas::widget_size()
{
	return sge::gui::dim(
		static_cast<unit>(view().width()),
		static_cast<unit>(view().height()));
}

void sge::gui::canvas::draw_rect(
	rect const &rel_rect,
	color const c,
	rect_type::type const t)
{
	SGE_LOG_DEBUG(
		mylogger,log::_1 << "draw_rect: rel_rect: " << rel_rect 
		                 << " (dimension: " << rel_rect.dim() << ", position: " 
										 << rel_rect.pos());

	rect const abs_rect(rel_rect.pos()+widget_pos(),rel_rect.dim());

	SGE_LOG_DEBUG(mylogger,log::_1 << "widget position is " << widget_pos());

	// rect is not (completely) inside area?
	SGE_ASSERT_MESSAGE(
		math::contains(widget_area(),abs_rect),SGE_TEXT("tried to draw a rect ")+
		boost::lexical_cast<string>(abs_rect)+
		SGE_TEXT(" which is not completely inside the widget rect ")+
		boost::lexical_cast<string>(widget_area()));
	
	SGE_LOG_DEBUG(mylogger,log::_1 << "trying to draw rect " <<  abs_rect << " (absolute)");
	
	// draw not the whole rect but only the intersection of the rect with the
	// locked area. if they don't intersect, nothing is to be drawn
	if (!math::intersects(abs_rect,invalid_area()))
	{
		SGE_LOG_DEBUG(
			mylogger,log::_1 << "rect " << abs_rect << " and invalid area " 
			                 << invalid_area() << " don't intersect, returning");
		return;
	}

	math::rect<int> const is =
		math::structure_cast<int>(math::intersection(abs_rect,invalid_area()));

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << "rect " << abs_rect << " and invalid area " 
		        << invalid_area() << " intersection " << is);

	switch (t)
	{
		case rect_type::filled:
		{
			SGE_LOG_DEBUG(
				mylogger,
				log::_1 << SGE_TEXT("chose type 'filled', so filling sub view ") 
				        << is.left()-invalid_area().left() << "," 
				        << is.top()-invalid_area().top() << "," << is.w() 
								<< "," << is.h());

			renderer::fill_pixels(
				boost::gil::subimage_view(
					view(),
					is.left()-invalid_area().left(),
					is.top()-invalid_area().top(),
					is.w(),
					is.h()
					)
			,c);
		}
		break;
		case rect_type::outline:
		{
			// clipping is handled inside draw_line_strip or draw_line respectively
			point_container ps;
			ps.push_back(point(point(rel_rect.left(),rel_rect.top())));
			ps.push_back(point(point(rel_rect.right()-1,rel_rect.top())));
			ps.push_back(point(point(rel_rect.right()-1,rel_rect.bottom()-1)));
			ps.push_back(point(point(rel_rect.left(),rel_rect.bottom()-1)));
			draw_line_strip(ps,c,false,true);
		}
		break;
	}
}

void sge::gui::canvas::draw_line_strip(
	point_container const &points,
	color const c,
	bool const dashed,
	bool const loop)
{
	SGE_ASSERT(points.size() > 1);
	
	for (point_container::size_type i = static_cast<point_container::size_type>(0); 
		i < static_cast<point_container::size_type>(points.size()-1); 
		++i)
		draw_line(points[i],points[i+1],c,dashed);

	if (loop)
		draw_line(points[points.size()-1],points[0],c,dashed);
}

sge::gui::canvas::view_type sge::gui::canvas::sub_view(rect const &r)
{
	return boost::gil::subimage_view(
		view(),
		static_cast<int>(r.left()),
		static_cast<int>(r.top()),
		static_cast<int>(r.w()),
		static_cast<int>(r.h())
		);
}

void sge::gui::canvas::blit_font(
	point const &pos,
	font::const_image_view const &data,
	color const fg)
{
	SGE_LOG_DEBUG(mylogger,log::_1 << "character height is " << data.height() 
						                     << ", drawing it at position " << pos);

	point const abs_pos = widget_pos() + pos;

	// absolute data area
	rect const abs_data_area(
		abs_pos,
		dim(
			static_cast<unit>(data.width()),
			static_cast<unit>(data.height())
		));

	SGE_LOG_DEBUG(mylogger,log::_1 << "trying to draw a character at " << abs_data_area);
		
	// if the character to be drawn and the invalid area don't even intersect,
	// then leave it out
	if (!math::intersects(abs_data_area,invalid_area()))
	{
		SGE_LOG_DEBUG(
			mylogger,
			log::_1 << abs_data_area << " and invalid area " 
			        << invalid_area() << " do not intersect, returning");
		return;
	}
	
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << abs_data_area << " and invalid area " 
		        << invalid_area() << " intersect, continuing");

	// calculate absolute intersection between invalid and data area
	rect const is_abs = math::intersection(abs_data_area,invalid_area());

	SGE_LOG_DEBUG(mylogger,log::_1 << "absolute intersection is: " << is_abs);

	// calculate rect which is relative to data (and make it 'int' 'cause gil wants it
	// that way
	math::rect<int> const is_rel_data(
		static_cast<int>(is_abs.left()-abs_pos.x()),
		static_cast<int>(is_abs.top()-abs_pos.y()),
		static_cast<int>(is_abs.right()-abs_pos.x()),
		static_cast<int>(is_abs.bottom()-abs_pos.y())
	);

	SGE_LOG_DEBUG(mylogger,log::_1 << "intersection relative to data is: " << is_rel_data);

	// calculate rect relative to invalid_rect
	rect const is_rel_invalid(
		is_abs.left()-invalid_area().left(),
		is_abs.top()-invalid_area().top(),
		is_abs.right()-invalid_area().left(),
		is_abs.bottom()-invalid_area().top()
	);

	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << "intersection relative to invalid rect is: " << is_rel_invalid);
	
	sge::renderer::transform_pixels(
		boost::gil::subimage_view(
			data,
			is_rel_data.left(),
			is_rel_data.top(),
			is_rel_data.w(),
			is_rel_data.h()
			),
		renderer::make_const_image_view(sub_view(is_rel_invalid)),
		sub_view(is_rel_invalid),
		utility::font_blitter(fg));
}

void sge::gui::canvas::draw_text(
	string const &text,
	point const &pos,
	dim const &max_size,
	font::align_h::type h,
	font::align_v::type v,
	font::flag_t f)
{
	SGE_ASSERT_MESSAGE(metrics,SGE_TEXT("no metrics set!"));
	SGE_ASSERT_MESSAGE(font,SGE_TEXT("no font set!"));
	font->draw_text(text,pos,max_size,h,v,f);
}

void sge::gui::canvas::draw_pixel(point const &p,color const c)
{
	// transform coordinate relative to widget origin to absolute coordinate
	point const p_abs = widget_pos() + p;
	
	if (!math::contains(invalid_area(),p_abs))
		return;
	
	// transform pixel coordinate (which is relative to the widget origin)
	// to a position relative to the invalid area origin
	point const tf = p_abs - point(invalid_area().left(),invalid_area().top());
	boost::gil::apply_operation(
		boost::gil::subimage_view(
			view(),
			tf.x(),
			tf.y(),
			1,
			1),
		utility::set_pixel(c));
}

void sge::gui::canvas::draw_line(
	point const &a,
	point const &b,
	color const color_,
	bool const dashed)
{
	SGE_ASSERT_MESSAGE(
		math::contains(widget_area(),widget_pos() + a) && 
		math::contains(widget_area(),widget_pos() + b),
		(format(SGE_TEXT("tried to draw a line from %1% to %2%, which is out of the widget area %3%")) % (widget_pos() + a) % (widget_pos() + b) % widget_area()).str());

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

		if (!dashed || (count++) % 2 == 0)
			draw_pixel(pos,color_);
	}
}
