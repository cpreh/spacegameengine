#include "main.hpp"
#include "testbed.hpp"
#include <rucksack/widget/master_and_slaves.hpp>
#include <rucksack/widget/viewport_adaptor.hpp>
#include <rucksack/widget/dummy.hpp>
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
rucksack::examples::main(
	awl::main::function_context const &)
try
{
	rucksack::examples::testbed testbed_(
		sge::window::title(
			FCPPT_TEXT("rucksack master and slaves test")));

	rucksack::widget::viewport_adaptor viewport_box(
		testbed_.systems().viewport_manager(),
		testbed_.systems().renderer());

	rucksack::widget::master_and_slaves mas_box(
		rucksack::padding(
			5));

	viewport_box.child(
		mas_box);

	typedef fcppt::random::generator::minstd_rand default_generator;

	default_generator def_gen(
		fcppt::random::generator::seed_from_chrono<
			default_generator::seed
		>());

	typedef fcppt::random::distribution::uniform_int<
		rucksack::scalar
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
	boost::ptr_vector<rucksack::widget::dummy>
	dummy_sprite_sequence;

	dummy_sprite_sequence sprites;

	testbed_.add_widget(
		viewport_box,
		sge::image::colors::blue());

	rucksack::widget::dummy master_dummy(
		rucksack::axis_policy2(
			rucksack::axis_policy(
				rucksack::minimum_size(
					size_rng_w()),
				rucksack::preferred_size(
					rucksack::optional_scalar()),
				rucksack::is_expanding(
					false)),
			rucksack::axis_policy(
				rucksack::minimum_size(
					size_rng_h()),
				rucksack::preferred_size(
					rucksack::optional_scalar()),
				rucksack::is_expanding(
					false)),
			rucksack::aspect(
				1,
				1)));

	mas_box.master_pane(
		master_dummy);

	testbed_.add_widget(
		master_dummy,
		sge::image::colors::cyan());

	for(unsigned i = 0; i < 5; ++i)
	{
		fcppt::container::ptr::push_back_unique_ptr(
			sprites,
			fcppt::make_unique_ptr<rucksack::widget::dummy>(
				rucksack::axis_policy2(
					rucksack::axis_policy(
						rucksack::minimum_size(
							size_rng_w()),
						rucksack::preferred_size(
							rucksack::optional_scalar()),
						rucksack::is_expanding(
							false)),
					rucksack::axis_policy(
						rucksack::minimum_size(
							size_rng_h()),
						rucksack::preferred_size(
							rucksack::optional_scalar()),
						rucksack::is_expanding(
							false)),
					rucksack::aspect(
						1,
						1))));

		mas_box.push_back_child(
			sprites.back());

		testbed_.add_widget(
			sprites.back(),
			sge::image::colors::red());
	}

	return testbed_.run();
}
catch(
	fcppt::exception const &error)
{
	fcppt::io::cerr()
		<< error.string()
		<< FCPPT_TEXT('\n');

	return awl::main::exit_failure();
}
