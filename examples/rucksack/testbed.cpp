#include "testbed.hpp"
#include "testbed_impl.hpp"
#include <awl/main/exit_code.hpp>
#include <fcppt/make_unique_ptr.hpp>

rucksack::examples::testbed::testbed(
	sge::window::title const &_str)
:
	impl_(
		fcppt::make_unique_ptr<examples::testbed_impl>(
			_str))
{
}

void
rucksack::examples::testbed::add_widget(
	widget::base &_widget,
	sge::image::color::any::object const &_color)
{
	return
		impl_->add_widget(
			_widget,
			_color);
}

awl::main::exit_code const
rucksack::examples::testbed::run()
{
	return
		impl_->run();
}

sge::systems::instance const &
rucksack::examples::testbed::systems() const
{
	return
		impl_->systems();
}

rucksack::examples::testbed::~testbed()
{
}
