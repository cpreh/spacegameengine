//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_STATE_DETAIL_MAKE_ONE_OBJECT_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_MAKE_ONE_OBJECT_HPP_INCLUDED

#include <sge/sprite/state/render_device.hpp>
#include <sge/sprite/state/detail/device_for_state.hpp>
#include <sge/sprite/state/detail/parameters_class.hpp>
#include <fcppt/not.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/mpl/arg.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/constant.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/front.hpp>
#include <fcppt/mpl/list/keep_if.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::state::detail
{

template <typename StateChoices>
class make_one_object
{
public:
  using render_device = sge::sprite::state::render_device<StateChoices>;

  using parameters_class = sge::sprite::state::detail::parameters_class<StateChoices>;

  make_one_object(
      fcppt::reference<render_device> const _render_device, parameters_class const &_parameters)
      : render_device_(_render_device), parameters_(_parameters)
  {
  }

private:
  template <typename State, typename Role>
  using state_has_role = std::is_same<typename State::role, Role>;

  template <typename Role>
  using state_for_role = fcppt::mpl::list::front<fcppt::mpl::list::keep_if<
      typename StateChoices::optional_elements,
      fcppt::mpl::bind<
          fcppt::mpl::lambda<state_has_role>,
          fcppt::mpl::arg<1>,
          fcppt::mpl::constant<Role>>>>;

public:
  template <typename Type, typename Role>
  std::enable_if_t<
      state_for_role<Role>::persistent::value,
      typename state_for_role<Role>::state_type>
  operator()(fcppt::record::element<Role, Type>) const
  {
    return state_for_role<Role>::make(
        fcppt::reference_to_base<
            sge::sprite::state::detail::device_for_state<state_for_role<Role>>>(render_device_),
        fcppt::record::get<typename state_for_role<Role>::parameter_role>(parameters_.get()));
  }

  template <typename Type, typename Role>
  std::enable_if_t<
      fcppt::not_(state_for_role<Role>::persistent::value),
      fcppt::optional::object<typename state_for_role<Role>::state_type>>
  operator()(fcppt::record::element<Role, Type>) const
  {
    return fcppt::optional::object<typename state_for_role<Role>::state_type>();
  }

private:
  fcppt::reference<render_device> render_device_;

  fcppt::reference<parameters_class const> parameters_;
};

}

#endif
