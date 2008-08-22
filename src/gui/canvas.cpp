#include <sge/gui/canvas.hpp>
#include <sge/gui/font_drawer_canvas.hpp>

#include <sge/math/rect_impl.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/math/signum.hpp>
#include <sge/format.hpp>
#include <sge/assert.hpp>
#include <sge/iostream.hpp>

#include <boost/gil/extension/dynamic_image/algorithm.hpp>
#include <boost/gil/extension/dynamic_image/apply_operation.hpp>
#include <boost/gil/extension/dynamic_image/image_view_factory.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

#include <algorithm>

#include <cmath>
#include <cstdlib>

namespace
{
struct converter 
{
	converter(sge::renderer::color const fg,sge::renderer::color const bg) : fg(fg),bg(bg) {}

	template<typename T>
	void operator()(sge::font::color const src,T &dest) const;

	sge::renderer::color const fg,bg;
};

// FIXME: make this more clean: check T's channel count and determine which one is the alpha channel, then convert
// the input to this function in 'src' is a gray value, 'dest' is rgba8
template<typename T>
void converter::operator()(
  sge::font::color const src,
	T &dest) const
{ 
	float const ratio = static_cast<float>(src)/255.0f;

	for (unsigned i = 0; i <= 2; ++i)
		dest[i] = static_cast<sge::renderer::pixel_channel_8>(
			static_cast<float>(fg[i])*ratio+static_cast<float>(bg[i])*(1.0f-ratio));
	
	dest[3] = static_cast<sge::renderer::pixel_channel_8>(255);
}

struct set_pixel_fn
{
	sge::gui::canvas::color_type const c;
	sge::gui::point const p;

	set_pixel_fn(
		sge::gui::canvas::color_type const c,
		sge::gui::point const p) 
		: c(c),p(p) {}

	typedef void result_type;

	template<typename T>
	result_type operator()(T &view) const
	{
		view(p.x(),p.y()) = c;
	}
};

template<typename T,std::size_t n,typename F>
sge::math::basic_vector<T,n> apply(sge::math::basic_vector<T,n> const &v,F f)
{
	sge::math::basic_vector<T,n> newone = v;
	std::transform(newone.begin(),newone.end(),newone.begin(),f);
	//BOOST_FOREACH(T &c,newone)
	//	c = f(c);
	return newone;
}
}

sge::gui::canvas::canvas(
	view_type const &texture_,
	rect const &widget_,
	rect const &invalid_)
	: texture_(texture_),
		widget_(widget_),
		invalid_(invalid_),
	  drawer(new font_drawer_canvas(*this))
{
}

void sge::gui::canvas::reset_font(
	font::metrics_ptr _metrics,
	color_type const fg,
	color_type const bg)
{
	metrics = _metrics;

	// temporarily convert to canvas_drawer to set foreground and background
	font_drawer_canvas &cd = static_cast<font_drawer_canvas &>(*drawer);
	cd.fg(fg);
	cd.bg(bg);

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
	color_type const c,
	rect_type::type const t)
{
	cerr << "canvas: draw_rect: rel_rect: " << rel_rect << " (dimension: " << rel_rect.dim() << ", position: " << rel_rect.pos() << ")\n";

	rect const abs_rect(rel_rect.pos()+widget_pos(),rel_rect.dim());

	//cerr << "canvas: widget position is " << widget_pos() << "\n";

	// rect is not (completely) inside area?
	SGE_ASSERT_MESSAGE(
		math::contains(widget_area(),abs_rect),SGE_TEXT("tried to draw a rect ")+
		boost::lexical_cast<string>(abs_rect)+
		SGE_TEXT(" which is not completely inside the widget rect ")+
		boost::lexical_cast<string>(widget_area()));
	
	//cerr << "canvas: trying to draw rect " <<  abs_rect << " (absolute)\n";
	
	// draw not the whole rect but only the intersection of the rect with the
	// locked area. if they don't intersect, nothing is to be drawn
	if (!math::intersects(abs_rect,invalid_area()))
	{
		//cerr << "canvas: rect " << abs_rect << " and invalid area " << invalid_area() << " don't intersect, returning\n";
		return;
	}

	math::basic_rect<int> const is =
		math::structure_cast<int>(math::intersection(abs_rect,invalid_area()));

	//cerr << "canvas: rect " << abs_rect << " and invalid area " << invalid_area() << " intersection " << is << "\n";

	switch (t)
	{
		case rect_type::filled:
		{
			//cerr << "chose type 'filled', so filling sub view " << is.left()-invalid_area().left() << "," 
			//	<< is.top()-invalid_area().top() << "," << is.w() << "," << is.h() << "\n";
			boost::gil::fill_pixels(
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
			draw_line_strip(ps,c,true);
		}
		break;
	}
}

void sge::gui::canvas::draw_line_strip(
	point_container const &points,
	color_type const c,
	bool const loop)
{
	SGE_ASSERT(points.size() > 1);
	
	for (point_container::size_type i = static_cast<point_container::size_type>(0); 
		i < static_cast<point_container::size_type>(points.size()-1); 
		++i)
		draw_line(points[i],points[i+1],c);

	if (loop)
		draw_line(points[points.size()-1],points[0],c);
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
	color_type const fg,
	color_type const bg)
{
	//cerr << "canvas: character height is " << data.height() 
	//					<< ", drawing it at position " << pos << "\n";
	point const abs_pos = widget_pos() + pos;

	// absolute data area
	rect const abs_data_area(
		abs_pos,
		dim(
			static_cast<unit>(data.width()),
			static_cast<unit>(data.height())
		));

	//cerr << "canvas: trying to draw a character at " << abs_data_area << "\n";
		
	// if the character to be drawn and the invalid area don't even intersect,
	// then leave it out
	if (!math::intersects(abs_data_area,invalid_area()))
	{
		//cerr << "canvas: " << abs_data_area << " and invalid area " << invalid_area() << " do not intersect, returning\n";
		return;
	}
	
	//cerr << "canvas: " << abs_data_area << " and invalid area " << invalid_area() << " intersect, continuing\n";

	// calculate absolute intersection between invalid and data area
	rect const is_abs = math::intersection(abs_data_area,invalid_area());

	//cerr << "canvas: absolute intersection is: " << is_abs << "\n";

	// calculate rect which is relative to data (and make it 'int' 'cause gil wants it
	// that way
	math::basic_rect<int> const is_rel_data(
		static_cast<int>(is_abs.left()-abs_pos.x()),
		static_cast<int>(is_abs.top()-abs_pos.y()),
		static_cast<int>(is_abs.right()-abs_pos.x()),
		static_cast<int>(is_abs.bottom()-abs_pos.y())
	);

	//cerr << "canvas: intersection relative to data is: " << is_rel_data << "\n";

	// calculate rect relative to invalid_rect
	rect const is_rel_invalid(
		is_abs.left()-invalid_area().left(),
		is_abs.top()-invalid_area().top(),
		is_abs.right()-invalid_area().left(),
		is_abs.bottom()-invalid_area().top()
	);

	//cerr << "canvas: intersection relative to invalid rect is: " << is_rel_invalid << "\n";
	
	converter conv(fg,bg);
	boost::gil::copy_and_convert_pixels(
		boost::gil::subimage_view(
			data,
			is_rel_data.left(),
			is_rel_data.top(),
			is_rel_data.w(),
			is_rel_data.h()
			),
		sub_view(is_rel_invalid),
		conv);
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

void sge::gui::canvas::draw_pixel(point const &p,color_type const c)
{
	// transform coordinate relative to widget origin to absolute coordinate
	point const p_abs = widget_pos() + p;
	
	if (!math::contains(invalid_area(),p_abs))
		return;
	
	// transform pixel coordinate (which is relative to the widget origin)
	// to a position relative to the invalid area origin
	point const tf = p_abs - point(invalid_area().left(),invalid_area().top());
	boost::gil::apply_operation(texture_,set_pixel_fn(c,tf));
}

void sge::gui::canvas::draw_line(point const &a,point const &b,color_type const color)
{
	//cerr << "canvas: checking if " << (widget_pos() + a) << " is inside of ";
	//cerr << widget_area() << ": " << math::contains(widget_area(),widget_pos() + a) << "\n";
	//cerr << "canvas: checking if " << (widget_pos() + b) << " is inside of " ;
	//cerr << widget_area() << ": " << math::contains(widget_area(),widget_pos() + b) << "\n";

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
	draw_pixel(pos,color);
 
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

		draw_pixel(pos,color);
	}
}
