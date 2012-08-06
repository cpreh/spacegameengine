#ifndef RUCKSACK_EXAMPLES_TESTBED_HPP_INCLUDED
#define RUCKSACK_EXAMPLES_TESTBED_HPP_INCLUDED

#include "testbed_impl_fwd.hpp"
#include <rucksack/widget/base_fwd.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/systems/instance_fwd.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace rucksack
{
namespace examples
{
class testbed
{
FCPPT_NONCOPYABLE(
	testbed);
public:
	explicit
	testbed(
		sge::window::title const &);

	void
	add_widget(
		widget::base &,
		sge::image::color::any::object const &);

	awl::main::exit_code const
	run();

	sge::systems::instance const &
	systems() const;

	~testbed();
private:
	fcppt::scoped_ptr<examples::testbed_impl> impl_;
};
}
}

#endif
