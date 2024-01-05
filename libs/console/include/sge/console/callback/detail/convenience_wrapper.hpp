//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CONSOLE_CALLBACK_DETAIL_CONVENIENCE_WRAPPER_HPP_INCLUDED
#define SGE_CONSOLE_CALLBACK_DETAIL_CONVENIENCE_WRAPPER_HPP_INCLUDED

#include <sge/console/arg_list.hpp>
#include <sge/console/object.hpp> // IWYU pragma: keep
#include <sge/console/object_ref.hpp>
#include <sge/console/callback/detail/conversion_visitor.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/string.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/algorithm/loop_break_mpl.hpp> // IWYU pragma: keep
#include <fcppt/algorithm/loop_break_tuple.hpp> // IWYU pragma: keep
#include <fcppt/algorithm/map_tuple.hpp> // IWYU pragma: keep
#include <fcppt/array/from_range.hpp>
#include <fcppt/array/object_impl.hpp>
#include <fcppt/mpl/function_args.hpp>
#include <fcppt/mpl/list/as_tuple.hpp>
#include <fcppt/mpl/list/indices.hpp>
#include <fcppt/mpl/list/size.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/sequence.hpp>
#include <fcppt/tuple/apply.hpp>
#include <fcppt/tuple/from_array.hpp>
#include <fcppt/tuple/init.hpp>
#include <fcppt/tuple/invoke.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace sge::console::callback::detail
{

template <typename FunctionType>
class convenience_wrapper
{
public:
  using function_type = FunctionType;

  template <typename Function>
  convenience_wrapper(Function &&_function, sge::font::string &&_short_description)
      : function_(std::forward<Function>(_function)),
        short_description_(std::move(_short_description))
  {
  }

  void
  operator()(sge::console::arg_list const &_args, sge::console::object_ref const _console) const
  {
    using arg_types = fcppt::mpl::function_args<function_type>;

    using arg_count = fcppt::mpl::list::size<arg_types>;

    using static_args = fcppt::array::object<sge::font::string, arg_count::value>;

    fcppt::optional::maybe(
        fcppt::array::from_range<arg_count::value>(
            // TODO(philipp): Range from begin + 1 to end?
            _args),
        [&_console, this]
        {
          _console.get().emit_error(SGE_FONT_LIT("Given too few or too many arguments!"));

          _console.get().emit_error(this->short_description_);
        },
        [&_console, this](static_args const &_static_args)
        {
          using arguments = fcppt::mpl::list::as_tuple<arg_types>;

          using interval = fcppt::mpl::list::indices<arg_types>;

          fcppt::optional::maybe_void(
              fcppt::optional::sequence<arguments>(fcppt::tuple::apply(
                  sge::console::callback::detail::conversion_visitor<arg_types>{_console},
                  fcppt::tuple::init<fcppt::mpl::list::as_tuple<interval>>(
                      [](auto const _index)
                      { return std::integral_constant<std::size_t, _index()>{}; }),
                  fcppt::tuple::from_array(_static_args))),
              [this](arguments &&_inner_args)
              { fcppt::tuple::invoke(this->function_, std::move(_inner_args)); });
        });
  }

private:
  fcppt::function<function_type> function_;

  sge::font::string short_description_;
};

}

#endif
