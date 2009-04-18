#include <sge/gui/detail/managers/mouse.hpp>
#include <sge/gui/detail/managers/compiler.hpp>
#include <sge/gui/detail/managers/render.hpp>
#include <sge/gui/detail/managers/time.hpp>
#include <sge/gui/detail/managers/keyboard.hpp>
#include <sge/gui/widgets/base.hpp>
#include <sge/gui/manager.hpp>
#include <sge/gui/log.hpp>
#include <sge/math/rect_impl.hpp>
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
	input::system_ptr const is,
	skins::ptr _skin,
	cursor_ptr _cursor)
:
	skin_(_skin),
	cursor_(_cursor),
	mouse_(
		new detail::managers::mouse(
			is,
			*cursor_)),
	render_(
		new detail::managers::render(
			rend,
			*cursor_)),
	keyboard_(
		new detail::managers::keyboard(
			is)),
	compiler_(
		new detail::managers::compiler(
			*mouse_,
			*render_)),
	timer_(
		new detail::managers::time())
{
	// TODO: find a way to initialize this in the constructor
	// that works for both gcc-4.3 and gcc-4.4.
	submanagers.push_back(compiler_.get());
	submanagers.push_back(mouse_.get());
	submanagers.push_back(keyboard_.get());
	submanagers.push_back(timer_.get());
	submanagers.push_back(render_.get());
}

sge::gui::manager::~manager() {}

void sge::gui::manager::dirty(
	widgets::base &w,
	rect const &r)
{
	BOOST_FOREACH(detail::submanager *m,submanagers)
		m->dirty(
			w,
			r);
}

void sge::gui::manager::invalidate(
	widgets::base &w,
	invalidation::type const &i)
{
	BOOST_FOREACH(detail::submanager *m,submanagers)
		m->invalidate(
			w,
			i);
}

sge::gui::timer::object_ptr const sge::gui::manager::register_timer(
	time::resolution const &r,
	timer::callback const cb)
{
	return timer_->add(r,cb);
}

void sge::gui::manager::update()
{
	BOOST_FOREACH(detail::submanager *m,submanagers)
		m->update();
}

void sge::gui::manager::draw()
{
	render_->draw();
}

sge::gui::cursor const &sge::gui::manager::cursor() const
{
	return *cursor_;
}

sge::gui::skins::base &sge::gui::manager::skin() 
{ 
	return *skin_; 
}

sge::gui::skins::base const &sge::gui::manager::skin() const
{ 
	return *skin_; 
}

sge::sprite::object &sge::gui::manager::connected_sprite(
	widgets::base &w)
{
	return render_->connected_sprite(w);
}

void sge::gui::manager::request_keyboard_focus(
	widgets::base &w)
{
	keyboard_->request_focus(w);
}

void sge::gui::manager::z(
	widgets::base &w,
	depth_type const _z)
{
	BOOST_FOREACH(detail::submanager *m,submanagers)
		m->z(
			w,
			_z);
}

void sge::gui::manager::add(
	widgets::base &w)
{
	BOOST_FOREACH(detail::submanager *m,submanagers)
		m->add(w);
}

void sge::gui::manager::remove(
	widgets::base &w)
{
	BOOST_FOREACH(detail::submanager *m,submanagers)
		m->remove(w);
}

void sge::gui::manager::resize(
	widgets::base &w,
	dim const &d)
{
	BOOST_FOREACH(detail::submanager *m,submanagers)
		m->resize(
			w,
			d);
}

void sge::gui::manager::reposition(
	widgets::base &w,
	point const &d)
{
	BOOST_FOREACH(detail::submanager *m,submanagers)
		m->reposition(
			w,
			d);
}

void sge::gui::manager::activation(
	widgets::base &w,
	activation_state::type const _n)
{
	BOOST_FOREACH(detail::submanager *m,submanagers)
		m->activation(w,_n);
}

void sge::gui::manager::keyboard_focus(
	widgets::base &w,
	keyboard_focus::type const f)
{
	keyboard_->keyboard_focus(
		w,
		f);
}
