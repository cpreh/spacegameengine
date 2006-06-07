#include "../vertical_scrollbar.hpp"
#include "../manager.hpp"
#include "../skin.hpp"
#include <boost/bind.hpp>

sge::gui::vertical_scrollbar::vertical_scrollbar(manager& m, element* const parent, const point pos, const dim sz, const bool visible, const bool enabled)
: rectangle(m,parent,pos,sz,skin::scrollbar_name,visible,enabled),
  s_pos(0),
  s_max(0),
  scrollbar(m,this,point(0,sz.w),dim(sz.w,sz.h-2*sz.w)),
  up_scroll_button(m,this,point(0,0),dim(sz.w,sz.w),scroll_button::up_scroll,boost::bind(&vertical_scrollbar::up_scroll_action,this)),
  down_scroll_button(m,this,point(0,sz.h-sz.w),dim(sz.w,sz.w),scroll_button::down_scroll,boost::bind(&vertical_scrollbar::down_scroll_action,this))
{}

void sge::gui::vertical_scrollbar::scroll_max(const size_type max)
{
	s_max = max; 
	scrollbar.height(scroll_max_h()/(s_max+1));
	if(s_pos > s_max)
		s_pos = s_max;
	recalc_pos();
}

void sge::gui::vertical_scrollbar::up_scroll_action()
{
	if(s_pos > 0)
		--s_pos;
	recalc_pos();
}

void sge::gui::vertical_scrollbar::down_scroll_action()
{
	if(s_pos < s_max)
		++s_pos;
	recalc_pos();
}

void sge::gui::vertical_scrollbar::on_glob_mouse_move(const mouse_move_event& event)
{
	if(!scrollbar.pressed())
		return;

	const point p = event.pos();
	const unit distx = 0.1f;
	if(p.y < 0 || p.y > height() || 
	   p.x < -distx || p.x > width() + distx)
		return;


	scrollbar.y(p.y-up_scroll_button.height());
	const unit miny = up_scroll_button.height();
	scrollbar.y(std::max(scrollbar.y(),miny));
	const unit maxy = scroll_max_h() + up_scroll_button.height() - scrollbar.height();
	scrollbar.y(std::min(scrollbar.y(),maxy));
	s_pos = static_cast<size_type>((scrollbar.y() - up_scroll_button.height()) / maxy) * (s_max+1);
}

void sge::gui::vertical_scrollbar::on_mouse_up(const mouse_button_event& event)
{
	if(event.code() == KC_MOUSEL)
		recalc_pos();
}

void sge::gui::vertical_scrollbar::on_mouse_press(const mouse_button_event& event)
{
	if(event.code() == KC_MOUSEL)
		move_scrollbar(event.pos());
}

void sge::gui::vertical_scrollbar::on_mouse_down(const mouse_button_event& event)
{
	if(event.code() == KC_MOUSEL)
		move_scrollbar(event.pos());
}

void sge::gui::vertical_scrollbar::move_scrollbar(const point click_pos)
{
	if(scrollbar.pressed())
		return;

	const size_type stride = 1;

	if(click_pos.y > scrollbar.y() + scrollbar.height())
	{
		s_pos += stride;
		if(s_pos > s_max)
			s_pos = s_max;
	}
	else if(click_pos.y < scrollbar.y())
	{
		if(s_pos >= stride)
			s_pos -= stride;
		else
			s_pos = 0;
	}
	recalc_pos();
}

void sge::gui::vertical_scrollbar::recalc_pos()
{
	scrollbar.y(scroll_max_h()*(static_cast<unit>(s_pos)/(s_max+1)) + up_scroll_button.height());
}

sge::gui::unit sge::gui::vertical_scrollbar::scroll_max_h() const
{
	return height()-2*up_scroll_button.height();
}
