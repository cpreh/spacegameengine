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
#include <sge/rucksack/testbed/object.hpp>
#include <sge/rucksack/testbed/systems.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <sge/rucksack/widget/enumeration.hpp>
#include <sge/rucksack/widget/viewport_adaptor.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>
#include <fcppt/random/generator/minstd_rand.hpp>
#include <fcppt/random/generator/seed_from_chrono.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
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
			FCPPT_TEXT("rucksack enumeration test")));

	sge::rucksack::widget::viewport_adaptor viewport_box(
		testbed.systems().viewport_manager(),
		testbed.systems().renderer_core());

	sge::rucksack::widget::enumeration enumeration_box(
		sge::rucksack::padding(
			5),
		sge::rucksack::aspect(
			1,
			1));

	viewport_box.child(
		enumeration_box);

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

	typedef
	boost::ptr_vector<sge::rucksack::widget::dummy>
	dummy_sprite_sequence;

	dummy_sprite_sequence sprites;

	testbed.add_widget(
		viewport_box,
		sge::image::color::predef::blue());

	for(unsigned i = 0; i < 20; ++i)
	{
		fcppt::container::ptr::push_back_unique_ptr(
			sprites,
			fcppt::make_unique_ptr<sge::rucksack::widget::dummy>(
				sge::rucksack::axis_policy2(
					sge::rucksack::axis_policy(
						sge::rucksack::minimum_size(
							size_rng_w()),
						sge::rucksack::preferred_size(
							sge::rucksack::optional_scalar()),
						sge::rucksack::is_expanding(
							false)),
					sge::rucksack::axis_policy(
						sge::rucksack::minimum_size(
							size_rng_h()),
						sge::rucksack::preferred_size(
							sge::rucksack::optional_scalar()),
						sge::rucksack::is_expanding(
							false)),
					sge::rucksack::aspect(
						1,
						1))));

		enumeration_box.push_back_child(
			sprites.back());

		testbed.add_widget(
			sprites.back(),
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
