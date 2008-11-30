#ifndef SGE_GUI_CANVAS_HPP_INCLUDED
#define SGE_GUI_CANVAS_HPP_INCLUDED

#include "types.hpp"
#include "../export.hpp"
#include "../renderer/texture.hpp"
#include "../font/types.hpp"
#include "../font/font_fwd.hpp"
#include "../font/font.hpp"

#include <boost/scoped_ptr.hpp>

#include <vector>

namespace sge
{
namespace gui
{
namespace rect_type
{
enum type { outline,filled };
}

// TODO: canvas has to accept three parameters: invalid_rect, widget_rect and the view. 
// widget_rect and invalid_rect have to be absolute rects. the drawing functions get coordinates 
// (relative to the widget's local area) and have to translate those local
// coordinates to coordinates which are relative to the invalid area's origin
class canvas
{
	public:
	typedef renderer::image_view view_type;
	typedef renderer::const_image_view const_view_type;
	typedef std::vector<point> point_container;

	SGE_SYMBOL canvas(view_type const &,rect const &widget_rect,rect const &invalid_rect);
	SGE_SYMBOL dim const widget_size();
	rect const widget_area() const { return widget_; }
	rect const invalid_area() const { return invalid_; }
	point const widget_pos() const { return point(widget_area().left(),widget_area().top()); }
	SGE_SYMBOL void draw_rect(rect const &,color,rect_type::type);
	SGE_SYMBOL void draw_text(
		string const &,
		point const &,
		dim const &max_size,
		font::align_h::type,
		font::align_v::type,
		font::flag_t = font::flags::default_);
	SGE_SYMBOL void draw_line(
		point const &,
		point const &,
		color,
		bool dashed = false);
	SGE_SYMBOL void draw_line_strip(
		point_container const &,
		color,
		bool dashed = false,
		bool loop = true);
	SGE_SYMBOL void reset_font(font::metrics_ptr,color fg);
	SGE_SYMBOL void draw_pixel(point const &,color);
	view_type view() { return texture_; }
	view_type view() const { return texture_; }
	private:
	view_type const texture_;
	rect const widget_;
	rect const invalid_;
	sge::font::drawer_ptr const drawer;
	sge::font::metrics_ptr metrics;
	sge::font::font_ptr font;

	view_type sub_view(rect const &);
	
	friend class font_drawer_canvas;
	void blit_font(
		point const &,
		font::const_image_view const &,
		color fg);
};
}
}

#endif
