#include <cmath>
#include "../list.hpp"
#include "../manager.hpp"
#include "../skin.hpp"

sge::gui::list::list(manager& m, element* const parent, const point pos, const dim sz, const unit line_height, const color text_color, const bool visible, const bool enabled)
: rectangle(m,parent,pos,sz,skin::list_background_name,visible,enabled),
  my_font(m.get_font()),
  text_color(text_color),
  line_height(line_height),
  vscrollbar(m,this,point(sz.w-0.02f,0),dim(0.02f,sz.h)),
  selected_(no_selection)
{}

void sge::gui::list::on_draw(const draw_event& event)
{
	rectangle::on_draw(event);

	const size_type scroll_pos = vscrollbar.scroll_pos();
	size_type max = size_type(height() / line_height) + scroll_pos;
	max = std::min(max,elements.size());

	const text_flag_t flags = TXTF_AlignLeft | TXTF_AlignTop | TXTF_NoMultiLine;
	my_font.font_height(line_height);
	for(size_type i = scroll_pos; i < max; ++i)
	{
		if(i == static_cast<size_type>(selected_))
			m.draw_selection(point(event.pos().x,event.pos().y+line_height*(i-scroll_pos)),
					 dim(width(),line_height));
		my_font.draw_text(elements.at(i),point(event.pos().x,event.pos().y+line_height*(i-scroll_pos)),
		                  dim(width(),line_height*2),text_color,flags);
	}
}

void sge::gui::list::on_click(const mouse_button_event& event)
{
	const size_type sel = vscrollbar.scroll_pos() + static_cast<size_type>(event.pos().y / line_height);
	if(sel < elements.size())
		selected_ = sel;
}

void sge::gui::list::push_back(const std::string& str)
{
	elements.push_back(str);
	calc_scrollbar();
}

void sge::gui::list::pop_back()
{
	if(elements.size() == 0)
		return;
	elements.pop_back();
	if(static_cast<size_type>(selected_) == elements.size())
		--selected_;
	calc_scrollbar();
}

void sge::gui::list::delete_element(const size_type index)
{
	if(index >= elements.size())
		return;
	elements.erase(elements.begin()+index);
	if(static_cast<size_type>(selected_) == elements.size())
		--selected_;
	calc_scrollbar();
}

void sge::gui::list::clear()
{
	elements.clear();
	selected_ = no_selection;
	calc_scrollbar();
}

sge::gui::list::size_type sge::gui::list::size() const { return elements.size(); }

sge::gui::list::difference_type sge::gui::list::selected_index() const { return selected_; }

const std::string& sge::gui::list::operator[](const size_type index) const { return elements[index]; }
std::string& sge::gui::list::operator[](const size_type index) { return elements[index]; }

const std::string& sge::gui::list::selected() const
{
	if(selected_ == no_selection)
		throw std::runtime_error("No selection made in gui::list!");
	return elements[selected_];
}


void sge::gui::list::calc_scrollbar()
{
	vscrollbar.scroll_max(elements.size()*line_height > height() ?
		static_cast<size_type>(std::ceil((elements.size()*line_height-height())/line_height))+1 :
		0);
}

