//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RUCKSACK_TESTBED_OBJECT_HPP_INCLUDED
#define SGE_RUCKSACK_TESTBED_OBJECT_HPP_INCLUDED

#include <sge/image/color/any/object_fwd.hpp>
#include <sge/rucksack/testbed/object_impl_fwd.hpp>
#include <sge/rucksack/testbed/systems_fwd.hpp>
#include <sge/rucksack/testbed/detail/symbol.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/systems/instance_fwd.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace rucksack
{
namespace testbed
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	SGE_RUCKSACK_TESTBED_DETAIL_SYMBOL
	explicit
	object(
		sge::window::title const &
	);

	SGE_RUCKSACK_TESTBED_DETAIL_SYMBOL
	void
	add_widget(
		sge::rucksack::widget::base &,
		sge::image::color::any::object const &
	);

	SGE_RUCKSACK_TESTBED_DETAIL_SYMBOL
	awl::main::exit_code
	run();

	SGE_RUCKSACK_TESTBED_DETAIL_SYMBOL
	sge::rucksack::testbed::systems const &
	systems() const;

	SGE_RUCKSACK_TESTBED_DETAIL_SYMBOL
	~object();
private:
	fcppt::unique_ptr<
		sge::rucksack::testbed::object_impl
	> const impl_;
};

}
}
}

#endif
