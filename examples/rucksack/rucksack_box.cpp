/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/testbed/object.hpp>
#include <sge/rucksack/testbed/systems.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <sge/rucksack/widget/viewport_adaptor.hpp>
#include <sge/rucksack/widget/box/base.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <example_main.hpp>
#include <fcppt/config/external_end.hpp>


awl::main::exit_code const
example_main(
	awl::main::function_context const &)
try
{
	sge::rucksack::testbed::object testbed(
		sge::window::title(
			FCPPT_TEXT("rucksack box test")));

	sge::rucksack::widget::viewport_adaptor viewport_box(
		testbed.systems().viewport_manager(),
		testbed.systems().renderer_core());

	sge::rucksack::widget::box::base outer_box(
		sge::rucksack::axis::x,
		sge::rucksack::aspect(
			1,
			1));

	viewport_box.child(
		outer_box);

	sge::rucksack::widget::box::base left_box(
		sge::rucksack::axis::y,
		sge::rucksack::aspect(
			1,
			1));

	outer_box.push_back_child(
		left_box,
		sge::rucksack::alignment::left_or_top);

	sge::rucksack::widget::box::base right_box(
		sge::rucksack::axis::y,
		sge::rucksack::aspect(
			1,
			1));

	outer_box.push_back_child(
		right_box,
		sge::rucksack::alignment::center);

	sge::rucksack::widget::dummy inner_sprite(
		sge::rucksack::axis_policy2(
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					100),
				sge::rucksack::preferred_size(
					sge::rucksack::optional_scalar()),
				sge::rucksack::is_expanding(
					false)),
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					50),
				sge::rucksack::preferred_size(
					sge::rucksack::optional_scalar()),
				sge::rucksack::is_expanding(
					false)),
			sge::rucksack::aspect(
				1,
				1)));

	left_box.push_back_child(
		inner_sprite,
		sge::rucksack::alignment::center);

	sge::rucksack::widget::dummy inner_sprite2(
		sge::rucksack::axis_policy2(
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					200),
				sge::rucksack::preferred_size(
					sge::rucksack::optional_scalar()),
				sge::rucksack::is_expanding(
					false)),
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					50),
				sge::rucksack::preferred_size(
					sge::rucksack::optional_scalar()),
				sge::rucksack::is_expanding(
					false)),
			sge::rucksack::aspect(
				1,
				1)));

	right_box.push_back_child(
		inner_sprite2,
		sge::rucksack::alignment::right_or_bottom);

	testbed.add_widget(
		viewport_box,
		sge::image::color::predef::blue());

	testbed.add_widget(
		inner_sprite,
		sge::image::color::predef::red());

	testbed.add_widget(
		inner_sprite2,
		sge::image::color::predef::green());

	return testbed.run();
}
catch(
	fcppt::exception const &error)
{
	fcppt::io::cerr()
		<< error.string()
		<< FCPPT_TEXT('\n');

	return awl::main::exit_failure();
}
