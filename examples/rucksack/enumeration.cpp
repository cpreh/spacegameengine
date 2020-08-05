//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/rucksack/testbed/object.hpp>
#include <sge/rucksack/testbed/systems.hpp>
#include <sge/rucksack/viewport/adaptor.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <sge/rucksack/widget/enumeration.hpp>
#include <awl/show_error.hpp>
#include <awl/show_error_narrow.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/container/array/init_move.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>
#include <fcppt/random/generator/minstd_rand.hpp>
#include <fcppt/random/generator/seed_from_chrono.hpp>
#include <fcppt/config/external_begin.hpp>
#include <example_main.hpp>
#include <array>
#include <exception>
#include <fcppt/config/external_end.hpp>


awl::main::exit_code
example_main(
	awl::main::function_context const &
)
try
{
	sge::rucksack::testbed::object testbed(
		sge::window::title(
			FCPPT_TEXT("rucksack enumeration test")
		)
	);

	sge::rucksack::viewport::adaptor viewport_box(
		fcppt::make_ref(
			testbed.systems().viewport_manager()
		),
		fcppt::make_ref(
			testbed.systems().renderer_device_core()
		)
	);

	sge::rucksack::widget::enumeration enumeration_box(
		sge::rucksack::padding(
			5 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		)
	);

	viewport_box.child(
		fcppt::reference_to_base<
			sge::rucksack::widget::base
		>(
			fcppt::make_ref(
				enumeration_box
			)
		)
	);

	using
	default_generator
	=
	fcppt::random::generator::minstd_rand;

	default_generator def_gen(
		fcppt::random::generator::seed_from_chrono<
			default_generator::seed
		>()
	);

	using
	scalar_distribution
	=
	fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_int<
			sge::rucksack::scalar
		>
	>;

	fcppt::random::variate<
		default_generator,
		scalar_distribution
	> size_rng_w(
		fcppt::make_ref(
			def_gen
		),
		scalar_distribution(
			scalar_distribution::param_type::min(
				10 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			),
			scalar_distribution::param_type::max(
				300 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			)
		)
	);

	fcppt::random::variate<
		default_generator,
		scalar_distribution
	> size_rng_h(
		fcppt::make_ref(
			def_gen
		),
		scalar_distribution(
			scalar_distribution::param_type::min(
				10 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			),
			scalar_distribution::param_type::max(
				300 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			)
		)
	);

	testbed.add_widget(
		fcppt::reference_to_base<
			sge::rucksack::widget::base
		>(
			fcppt::make_ref(
				viewport_box
			)
		),
		sge::image::color::any::object{
			sge::image::color::predef::blue()
		}
	);

	using
	dummy_unique_ptr
	=
	fcppt::unique_ptr<
		sge::rucksack::widget::dummy
	>;

	using
	dummy_sprite_sequence
	=
	std::array<
		dummy_unique_ptr,
		20 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	>;

	auto sprites(
		fcppt::container::array::init_move<
			dummy_sprite_sequence
		>(
			[
				&size_rng_w,
				&size_rng_h
			]
			{
				return
					fcppt::make_unique_ptr<
						sge::rucksack::widget::dummy
					>(
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
		enumeration_box.push_back_child(
			fcppt::reference_to_base<
				sge::rucksack::widget::base
			>(
				fcppt::make_ref(
					*dummy
				)
			)
		);

		testbed.add_widget(
			fcppt::reference_to_base<
				sge::rucksack::widget::base
			>(
				fcppt::make_ref(
					*dummy
				)
			),
			sge::image::color::any::object{
				sge::image::color::predef::red()
			}
		);
	}

	return
		testbed.run();
}
catch(
	fcppt::exception const &_error
)
{
	awl::show_error(
		_error.string()
	);

	return
		awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	awl::show_error_narrow(
		_error.what()
	);

	return
		awl::main::exit_failure();
}
