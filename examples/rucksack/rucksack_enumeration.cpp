#include <example_main.hpp>
#include <sge/rucksack/testbed/object.hpp>
#include <sge/rucksack/widget/enumeration.hpp>
#include <sge/rucksack/widget/viewport_adaptor.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <sge/systems/instance.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/color/any/object.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/uniform_int.hpp>
#include <fcppt/random/generator/minstd_rand.hpp>
#include <fcppt/random/generator/seed_from_chrono.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <boost/ptr_container/ptr_vector.hpp>
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
		testbed.systems().renderer());

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

	typedef fcppt::random::distribution::uniform_int<
		sge::rucksack::scalar
	> scalar_distribution;

	fcppt::random::variate<default_generator, scalar_distribution>
		size_rng_w(
			def_gen,
			scalar_distribution(
				scalar_distribution::min(
					10),
				scalar_distribution::max(
					300))),
		size_rng_h(
			def_gen,
			scalar_distribution(
				scalar_distribution::min(
					10),
				scalar_distribution::max(
					300)));

	typedef
	boost::ptr_vector<sge::rucksack::widget::dummy>
	dummy_sprite_sequence;

	dummy_sprite_sequence sprites;

	testbed.add_widget(
		viewport_box,
		sge::image::colors::blue());

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
			sge::image::colors::red());
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
