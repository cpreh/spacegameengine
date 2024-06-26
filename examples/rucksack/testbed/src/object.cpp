//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/color/any/object_fwd.hpp>
#include <sge/rucksack/testbed/object.hpp>
#include <sge/rucksack/testbed/systems_fwd.hpp>
#include <sge/rucksack/testbed/impl/object_impl.hpp>
#include <sge/rucksack/widget/reference.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::rucksack::testbed::object::object(sge::window::title &&_str)
    : impl_(fcppt::make_unique_ptr<sge::rucksack::testbed::object_impl>(std::move(_str)))
{
}

void sge::rucksack::testbed::object::add_widget(
    sge::rucksack::widget::reference const _widget, sge::image::color::any::object const &_color)
{
  impl_->add_widget(_widget, _color);
}

awl::main::exit_code sge::rucksack::testbed::object::run() { return impl_->run(); }

sge::rucksack::testbed::systems const &sge::rucksack::testbed::object::systems() const
{
  return impl_->systems();
}

sge::rucksack::testbed::object::~object() = default;
