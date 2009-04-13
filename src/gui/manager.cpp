#include <sge/gui/manager.hpp>
#include <sge/gui/widget.hpp>
#include <sge/gui/log.hpp>
#include <sge/math/rect_util.hpp>
#include <sge/font/system.hpp>
#include <sge/assert.hpp>
#include <sge/media.hpp>
#include <boost/foreach.hpp>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("manager"),
	false);
}

sge::gui::manager::manager(
	renderer::device_ptr const rend,
	sge::image::loader_ptr const il,
	input::system_ptr const is,
	font::system_ptr const fs,
	skin_ptr _skin,
	cursor_ptr _cursor)
:
	rend(rend),
	il(il),
	is(is),
	fs(fs),
	standard_font_(
		fs->create_font(
			sge::media_path() / SGE_TEXT("fonts/default.ttf"),
			15)),
	skin_(_skin),
	cursor_(_cursor),
	mouse_(
		is,
		il,
		rend,
		*cursor_),
	render_(
		rend,
		*cursor_),
	keyboard_(is),
	compiler_(
		mouse_,
		render_)
{
	// TODO: find a way to initialize this in the constructor
	// that works for both gcc-4.3 and gcc-4.4.
	submanagers.push_back(&mouse_);
	submanagers.push_back(&render_);
	submanagers.push_back(&keyboard_);
	submanagers.push_back(&compiler_);
	submanagers.push_back(&timer_);
}

void sge::gui::manager::dirty(
	widget &w,
	rect const &r)
{
	BOOST_FOREACH(detail::submanager *m,submanagers)
		m->dirty(
			w,
			r);
}

void sge::gui::manager::invalidate(
	widget &w)
{
	BOOST_FOREACH(detail::submanager *m,submanagers)
		m->invalidate(
			w);
}

sge::gui::timer::object_ptr const sge::gui::manager::register_timer(
	time::resolution const &r,
	timer::callback const cb)
{
	return timer_.add(r,cb);
}

void sge::gui::manager::update()
{
	BOOST_FOREACH(detail::submanager *m,submanagers)
		m->update();
}

void sge::gui::manager::draw()
{
	render_.draw();
}

sge::gui::cursor const &sge::gui::manager::cursor() const
{
	return *cursor_;
}

sge::font::metrics_ptr const sge::gui::manager::standard_font()
{
	return standard_font_;
}

sge::gui::skin &sge::gui::manager::skin() 
{ 
	return *skin_; 
}

sge::gui::skin const &sge::gui::manager::skin() const
{ 
	return *skin_; 
}

sge::sprite::object &sge::gui::manager::connected_sprite(
	widget &w)
{
	return render_.connected_sprite(w);
}


void sge::gui::manager::add(widget &w)
{
	BOOST_FOREACH(detail::submanager *m,submanagers)
		m->add(w);
}

void sge::gui::manager::remove(widget &w)
{
	BOOST_FOREACH(detail::submanager *m,submanagers)
		m->remove(w);
}

void sge::gui::manager::resize(widget &w,dim const &d)
{
	BOOST_FOREACH(detail::submanager *m,submanagers)
		m->resize(w,d);
}

void sge::gui::manager::reposition(widget &w,point const &d)
{
	BOOST_FOREACH(detail::submanager *m,submanagers)
		m->reposition(w,d);
}

void sge::gui::manager::activation(widget &w,activation_state::type const _n)
{
	BOOST_FOREACH(detail::submanager *m,submanagers)
		m->activation(w,_n);
}

sge::gui::detail::managers::keyboard &sge::gui::manager::keyboard()
{
	return keyboard_;
}

sge::gui::manager::~manager() {}
