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
#include <sge/rucksack/testbed/object.hpp>
#include <sge/rucksack/testbed/systems.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <sge/rucksack/widget/master_and_slaves.hpp>
#include <sge/rucksack/widget/viewport_adaptor.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/array_init_move.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>
#include <fcppt/random/generator/minstd_rand.hpp>
#include <fcppt/random/generator/seed_from_chrono.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <cstdlib>
#include <memory>
#include <example_main.hpp>
#include <fcppt/config/external_end.hpp>


awl::main::exit_code const
example_main(
	awl::main::function_context const &)
try
{
	sge::rucksack::testbed::object testbed(
		sge::window::title(
			FCPPT_TEXT("rucksack master and slaves test")));

	sge::rucksack::widget::viewport_adaptor viewport_box(
		testbed.systems().viewport_manager(),
		testbed.systems().renderer_device_core());

	sge::rucksack::widget::master_and_slaves mas_box(
		sge::rucksack::padding(
			5));

	viewport_box.child(
		mas_box);

	typedef fcppt::random::generator::minstd_rand default_generator;

	default_generator def_gen(
		fcppt::random::generator::seed_from_chrono<
			default_generator::seed
		>());

	typedef fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_int<
			sge::rucksack::scalar
		>
	> scalar_distribution;

	fcppt::random::variate<default_generator, scalar_distribution>
		size_rng_w(
			def_gen,
			scalar_distribution(
				scalar_distribution::param_type::min(
					10),
				scalar_distribution::param_type::max(
					300))),
		size_rng_h(
			def_gen,
			scalar_distribution(
				scalar_distribution::param_type::min(
					10),
				scalar_distribution::param_type::max(
					300)));

	testbed.add_widget(
		viewport_box,
		sge::image::color::predef::blue());

	sge::rucksack::widget::dummy master_dummy{
		sge::rucksack::axis_policy2(
			sge::rucksack::axis_policy(
				sge::rucksack::preferred_size(
					size_rng_w()
				)
			),
			sge::rucksack::axis_policy(
				sge::rucksack::preferred_size(
					size_rng_h()
				)
			)
		)
	};

	mas_box.master_pane(
		master_dummy);

	testbed.add_widget(
		master_dummy,
		sge::image::color::predef::cyan());

	typedef
	std::unique_ptr<
		sge::rucksack::widget::dummy
	>
	dummy_unique_ptr;

	typedef
	std::array<
		dummy_unique_ptr,
		5
	>
	dummy_unique_ptr_array;

	dummy_unique_ptr_array sprites(
		fcppt::algorithm::array_init_move<
			dummy_unique_ptr_array
		>(
			[
				&size_rng_w,
				&size_rng_h
			]
			{
				return
					fcppt::make_unique_ptr<sge::rucksack::widget::dummy>(
						sge::rucksack::axis_policy2(
							sge::rucksack::axis_policy(
								sge::rucksack::preferred_size(
									size_rng_w()
								)
							),
							sge::rucksack::axis_policy(
								sge::rucksack::preferred_size(
									size_rng_h()
								)
							)
						)
					);
			}
		)
	);

	for(
		auto const &dummy
		:
		sprites
	)
	{
		mas_box.push_back_child(
			*dummy
		);

		testbed.add_widget(
			*dummy,
			sge::image::color::predef::red());
	}

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
