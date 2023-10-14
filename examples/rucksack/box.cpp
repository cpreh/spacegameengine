//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/padding.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/testbed/object.hpp>
#include <sge/rucksack/testbed/systems.hpp> // NOLINT(misc-include-cleaner)
#include <sge/rucksack/viewport/adaptor.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/box.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <sge/window/title.hpp>
#include <awl/show_error.hpp>
#include <awl/show_error_narrow.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <example_main.hpp>
#include <exception>
#include <fcppt/config/external_end.hpp>

awl::main::exit_code example_main(awl::main::function_context const &)
try
{
  sge::rucksack::testbed::object testbed{sge::window::title{FCPPT_TEXT("rucksack box test")}};

  sge::rucksack::viewport::adaptor viewport_box{
      fcppt::make_ref(testbed.systems().viewport_manager()),
      fcppt::make_ref(testbed.systems().renderer_device_core())};

  sge::rucksack::padding const padding{
      5 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  };

  sge::rucksack::widget::box outer_box{sge::rucksack::axis::x, padding};

  viewport_box.child(
      fcppt::reference_to_base<sge::rucksack::widget::base>(fcppt::make_ref(outer_box)));

  sge::rucksack::widget::box left_box(sge::rucksack::axis::y, padding);

  outer_box.push_back_child(
      fcppt::reference_to_base<sge::rucksack::widget::base>(fcppt::make_ref(left_box)),
      sge::rucksack::alignment::left_or_top);

  sge::rucksack::widget::box right_box(sge::rucksack::axis::y, padding);

  outer_box.push_back_child(
      fcppt::reference_to_base<sge::rucksack::widget::base>(fcppt::make_ref(right_box)),
      sge::rucksack::alignment::center);

  sge::rucksack::widget::dummy inner_sprite{sge::rucksack::axis_policy2{
      sge::rucksack::axis_policy{sge::rucksack::preferred_size{
          100 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      }},
      sge::rucksack::axis_policy{sge::rucksack::preferred_size{
          50 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      }}}};

  left_box.push_back_child(
      fcppt::reference_to_base<sge::rucksack::widget::base>(fcppt::make_ref(inner_sprite)),
      sge::rucksack::alignment::center);

  sge::rucksack::widget::dummy inner_sprite2{sge::rucksack::axis_policy2{
      sge::rucksack::axis_policy{sge::rucksack::preferred_size{
          200 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      }},
      sge::rucksack::axis_policy{sge::rucksack::preferred_size{
          50 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      }}}};

  right_box.push_back_child(
      fcppt::reference_to_base<sge::rucksack::widget::base>(fcppt::make_ref(inner_sprite2)),
      sge::rucksack::alignment::right_or_bottom);

  testbed.add_widget(
      fcppt::reference_to_base<sge::rucksack::widget::base>(fcppt::make_ref(viewport_box)),
      sge::image::color::any::object{sge::image::color::predef::blue()});

  testbed.add_widget(
      fcppt::reference_to_base<sge::rucksack::widget::base>(fcppt::make_ref(inner_sprite)),
      sge::image::color::any::object{sge::image::color::predef::red()});

  testbed.add_widget(
      fcppt::reference_to_base<sge::rucksack::widget::base>(fcppt::make_ref(inner_sprite2)),
      sge::image::color::any::object{sge::image::color::predef::green()});

  return testbed.run();
}
catch (fcppt::exception const &_error)
{
  awl::show_error(_error.string());

  return awl::main::exit_failure();
}
catch (std::exception const &_error)
{
  awl::show_error_narrow(_error.what());

  return awl::main::exit_failure();
}
