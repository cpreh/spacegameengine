/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/padding.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/testbed/object.hpp>
#include <sge/rucksack/testbed/systems.hpp>
#include <sge/rucksack/viewport/adaptor.hpp>
#include <sge/rucksack/widget/box.hpp>
#include <sge/rucksack/widget/dummy.hpp>
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
	awl::main::function_context const &
)
try
{
	sge::rucksack::testbed::object testbed{
		sge::window::title{
			FCPPT_TEXT("rucksack box test")
		}
	};

	sge::rucksack::viewport::adaptor viewport_box{
		testbed.systems().viewport_manager(),
		testbed.systems().renderer_device_core()
	};

	sge::rucksack::padding const padding{
		5
	};

	sge::rucksack::widget::box outer_box{
		sge::rucksack::axis::x,
		padding
	};

	viewport_box.child(
		outer_box
	);

	sge::rucksack::widget::box left_box(
		sge::rucksack::axis::y,
		padding
	);

	outer_box.push_back_child(
		left_box,
		sge::rucksack::alignment::left_or_top
	);

	sge::rucksack::widget::box right_box(
		sge::rucksack::axis::y,
		padding
	);

	outer_box.push_back_child(
		right_box,
		sge::rucksack::alignment::center
	);

	sge::rucksack::widget::dummy inner_sprite{
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					100
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					50
				}
			}
		}
	};

	left_box.push_back_child(
		inner_sprite,
		sge::rucksack::alignment::center
	);

	sge::rucksack::widget::dummy inner_sprite2{
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					200
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					50
				}
			}
		}
	};

	right_box.push_back_child(
		inner_sprite2,
		sge::rucksack::alignment::right_or_bottom
	);

	testbed.add_widget(
		viewport_box,
		sge::image::color::predef::blue()
	);

	testbed.add_widget(
		inner_sprite,
		sge::image::color::predef::red()
	);

	testbed.add_widget(
		inner_sprite2,
		sge::image::color::predef::green()
	);

	return
		testbed.run();
}
catch(
	fcppt::exception const &error)
{
	fcppt::io::cerr()
		<< error.string()
		<< FCPPT_TEXT('\n');

	return awl::main::exit_failure();
}
