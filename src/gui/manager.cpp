#include <sge/gui/manager.hpp>
#include <sge/gui/widget.hpp>
#include <sge/gui/log.hpp>
#include <sge/font/system.hpp>
#include <sge/media.hpp>
#include <sge/iostream.hpp>

namespace
{
sge::gui::logger mylogger(sge::gui::global_log(),SGE_TEXT("manager"),true);
}


sge::gui::manager::manager(
	renderer::device_ptr const rend,
	sge::image::loader_ptr const il,
	input::system_ptr const is,
	font::system_ptr const fs,
	skin_ptr skin_)
	: rend(rend),
	  il(il),
	  is(is),
		fs(fs),
		standard_font_(
			fs->create_font(sge::media_path()/SGE_TEXT("fonts/default.ttf"),15)),
		skin_(skin_),
		mouse_(is,il,rend,*skin_),
		render_(rend,mouse_),
		keyboard_(is),
		updates_(mouse_,render_)
{
}

void sge::gui::manager::invalidate(
	rect const &r)
{
	render_.invalidate(r);
}

void sge::gui::manager::invalidate(
	widget &w)
{
	updates_.add(w);
}

sge::gui::timer::object_ptr const sge::gui::manager::register_timer(
	time::resolution const &r,
	timer::callback const cb)
{
	return timer_.add(r,cb);
}

void sge::gui::manager::draw()
{
	updates_.draw();
	render_.draw();
	timer_.draw();
}

sge::font::metrics_ptr const sge::gui::manager::standard_font()
{
	return standard_font_;
}

sge::gui::skin_ptr const sge::gui::manager::skin() 
{ 
	return skin_; 
}

sge::gui::const_skin_ptr const sge::gui::manager::skin() const
{ 
	return skin_; 
}

void sge::gui::manager::add(widget &w)
{
	keyboard_.add(w);
	mouse_.add(w);
	updates_.add(w);
	render_.add(w);
}

void sge::gui::manager::remove(widget &w)
{
	keyboard_.remove(w);
	mouse_.remove(w);
	updates_.remove(w);
	render_.remove(w);
}

void sge::gui::manager::resize(widget &w,dim const &d)
{
	render_.resize(w,d);
}

void sge::gui::manager::reposition(widget &w,point const &d)
{
	render_.reposition(w,d);
}

sge::gui::detail::keyboard_manager &sge::gui::manager::keyboard()
{
	return keyboard_;
}
