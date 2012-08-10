#include <sge/rucksack/testbed/object.hpp>
#include <sge/src/rucksack/testbed/object_impl.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


sge::rucksack::testbed::object::object(
	sge::window::title const &_str)
:
	impl_(
		fcppt::make_unique_ptr<
			sge::rucksack::testbed::object_impl>(
			_str))
{
}

void
sge::rucksack::testbed::object::add_widget(
	sge::rucksack::widget::base &_widget,
	sge::image::color::any::object const &_color)
{
	return
		impl_->add_widget(
			_widget,
			_color);
}

awl::main::exit_code const
sge::rucksack::testbed::object::run()
{
	return
		impl_->run();
}

sge::systems::instance const &
sge::rucksack::testbed::object::systems() const
{
	return
		impl_->systems();
}

sge::rucksack::testbed::object::~object()
{
}
