#ifndef SGE_RUCKSACK_TESTBED_OBJECT_HPP_INCLUDED
#define SGE_RUCKSACK_TESTBED_OBJECT_HPP_INCLUDED

#include <sge/image/color/any/object_fwd.hpp>
#include <sge/rucksack/testbed/object_impl_fwd.hpp>
#include <sge/rucksack/testbed/symbol.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/systems/instance_fwd.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/scoped_ptr_decl.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace rucksack
{
namespace testbed
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_RUCKSACK_TESTBED_SYMBOL
	explicit
	object(
		sge::window::title const &);

	SGE_RUCKSACK_TESTBED_SYMBOL
	void
	add_widget(
		sge::rucksack::widget::base &,
		sge::image::color::any::object const &);

	SGE_RUCKSACK_TESTBED_SYMBOL
	awl::main::exit_code const
	run();

	SGE_RUCKSACK_TESTBED_SYMBOL
	sge::systems::instance const &
	systems() const;

	SGE_RUCKSACK_TESTBED_SYMBOL
	~object();
private:
	fcppt::scoped_ptr<
		sge::rucksack::testbed::object_impl
	> const impl_;
};
}
}
}

#endif
