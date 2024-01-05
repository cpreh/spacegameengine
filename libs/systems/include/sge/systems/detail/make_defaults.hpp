//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SYSTEMS_DETAIL_MAKE_DEFAULTS_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_MAKE_DEFAULTS_HPP_INCLUDED

#include <sge/systems/detail/any_list.hpp>
#include <sge/systems/detail/extract_needs_init.hpp>
#include <sge/systems/detail/extract_parameter_type.hpp>
#include <sge/systems/detail/make_default_element.hpp>
#include <fcppt/algorithm/loop_break_mpl.hpp> // IWYU pragma: keep
#include <fcppt/algorithm/map.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/constant.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/contains.hpp>
#include <fcppt/mpl/list/from.hpp>
#include <fcppt/mpl/list/remove_if.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::systems::detail
{

template <typename Choices, typename Inits>
sge::systems::detail::any_list make_defaults()
{
  return fcppt::algorithm::map<sge::systems::detail::any_list>(
      fcppt::mpl::list::remove_if<
          Choices,
          fcppt::mpl::bind<
              fcppt::mpl::lambda<std::disjunction>,
              fcppt::mpl::lambda<sge::systems::detail::extract_needs_init>,
              fcppt::mpl::bind<
                  fcppt::mpl::lambda<fcppt::mpl::list::contains>,
                  fcppt::mpl::constant<fcppt::mpl::list::from<Inits>>,
                  fcppt::mpl::lambda<sge::systems::detail::extract_parameter_type>>>>{},
      [](auto const _type) { return sge::systems::detail::make_default_element(_type); });
}

}

#endif
