/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


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
