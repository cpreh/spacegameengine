//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/bvh/dummy_node.hpp>
#include <sge/bvh/object_impl.hpp>
#include <sge/bvh/tree_traits.hpp>
#include <fcppt/args_char.hpp>
#include <fcppt/args_from_second.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/main.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/strong_typedef_input.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/container/tree/depth.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/math/box/rect.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/options/argument.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/error_output.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/parse.hpp>
#include <fcppt/options/result_of.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_real.hpp>
#include <fcppt/random/generator/minstd_rand.hpp>
#include <fcppt/random/generator/seed_from_chrono.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <cstddef>
#include <exception>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>

namespace
{

FCPPT_DECLARE_STRONG_TYPEDEF(unsigned, rectangle_count);

void example_main(rectangle_count const _rectangle_count)
{
  using bvh_box = fcppt::math::box::rect<float>;

  using bvh_tree_traits = sge::bvh::tree_traits<sge::bvh::dummy_node, bvh_box, bvh_box>;

  bvh_box::dim const total_bounding_box{
      1024.0F, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      1024.0F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  };

  using generator_type = fcppt::random::generator::minstd_rand;

  generator_type generator{fcppt::random::generator::seed_from_chrono<generator_type::seed>()};

  using real_distribution = fcppt::random::distribution::basic<
      fcppt::random::distribution::parameters::uniform_real<float>>;

  using real_variate = fcppt::random::variate<generator_type, real_distribution>;

  real_variate screen_size_rng{
      fcppt::make_ref(generator),
      real_distribution(
          real_distribution::param_type::min(
              total_bounding_box.h() /
              8.0F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              ),
          real_distribution::param_type::sup(
              total_bounding_box.h() -
              total_bounding_box.h() /
                  8.0F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              ))};
  real_variate size_rng{
      fcppt::make_ref(generator),
      real_distribution(
          real_distribution::param_type::min(
              total_bounding_box.h() /
              16.0F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              ),
          real_distribution::param_type::sup(
              total_bounding_box.h() /
              4.0F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              ))};

  sge::bvh::object<bvh_tree_traits> bounding_hierarchy;

  auto const nodes(fcppt::algorithm::map<bvh_tree_traits::leaf_sequence>(
      fcppt::make_int_range_count(_rectangle_count.get()),
      [&screen_size_rng, &size_rng](auto)
      {
        bvh_box::dim const new_size{size_rng(), size_rng()};

        return bvh_box(
            bvh_box::vector(
                screen_size_rng(),
                screen_size_rng()) -
                (new_size /
                 2.0F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                 )
                    .get_unsafe(),
            new_size);
      }));

  using clock_type = std::chrono::steady_clock;

  clock_type::time_point const before{clock_type::now()};

  bounding_hierarchy.insert(nodes);

  fcppt::io::cout()
      << FCPPT_TEXT("Construction time: ")
      << std::chrono::duration_cast<std::chrono::milliseconds>(clock_type::now() - before).count()
      << FCPPT_TEXT('\n');

  fcppt::io::cout() << FCPPT_TEXT("Tree depth: ")
                    << fcppt::container::tree::depth(bounding_hierarchy.representation())
                    << FCPPT_TEXT('\n');
}

FCPPT_RECORD_MAKE_LABEL(rectangle_count_label);

}

int FCPPT_MAIN(int argc, fcppt::args_char *argv[])
try
{
  auto const parser(fcppt::options::argument<rectangle_count_label, rectangle_count>{
      fcppt::options::long_name{FCPPT_TEXT("rectangle-count")},
      fcppt::options::optional_help_text{}});

  using result_type = fcppt::options::result_of<decltype(parser)>;

  return fcppt::either::match(
      fcppt::options::parse(parser, fcppt::args_from_second(argc, argv)),
      [](fcppt::options::error const &_error)
      {
        fcppt::io::cerr() << _error << FCPPT_TEXT('\n');

        return EXIT_FAILURE;
      },
      [](result_type const &_result)
      {
        example_main(fcppt::record::get<rectangle_count_label>(_result));

        return EXIT_SUCCESS;
      });
}
catch (fcppt::exception const &_error)
{
  fcppt::io::cerr() << _error.string() << FCPPT_TEXT('\n');

  return EXIT_FAILURE;
}
catch (std::exception const &_error)
{
  std::cerr << _error.what() << '\n';

  return EXIT_FAILURE;
}
