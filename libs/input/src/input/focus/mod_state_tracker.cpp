//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/focus/mod_state_tracker.hpp>
#include <sge/input/focus/shared_ptr.hpp>
#include <sge/input/focus/event/base.hpp>
#include <sge/input/focus/event/discover.hpp>
#include <sge/input/focus/event/in.hpp>
#include <sge/input/focus/event/key.hpp>
#include <sge/input/focus/event/out.hpp>
#include <sge/input/focus/event/remove.hpp>
#include <sge/input/key/mod_state.hpp>
#include <sge/input/key/modifier.hpp>
#include <sge/input/key/pressed.hpp>
#include <sge/input/key/to_modifier.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/use.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/container/get_or_insert.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/enum/array_impl.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/enum/array_init.hpp>
#include <fcppt/enum/make_range.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/variant/apply.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::input::focus::mod_state_tracker::mod_state_tracker() : map_() {}

sge::input::focus::mod_state_tracker::~mod_state_tracker() = default;

void sge::input::focus::mod_state_tracker::event(sge::input::focus::event::base const &_event)
{
  fcppt::optional::maybe_void(
      fcppt::variant::dynamic_cast_<
          fcppt::mpl::list::object<
              sge::input::focus::event::discover const,
              sge::input::focus::event::in const,
              sge::input::focus::event::out const,
              sge::input::focus::event::key const,
              sge::input::focus::event::remove const>,
          fcppt::cast::dynamic_fun>(_event),
      [this](auto const &_variant)
      {
        sge::input::focus::shared_ptr const focus{
            fcppt::variant::apply([](auto const _ref) { return _ref.get().focus(); }, _variant)};

        auto const false_array(
            []
            {
              return fcppt::enum_::array_init<pressed_array>(
                  [](auto const _index)
                  {
                    FCPPT_USE(_index);

                    return sge::input::key::pressed{false};
                  });
            });

        auto const reset_pressed([this, focus, false_array](auto const &)
                                 { this->map_.insert(std::make_pair(focus, false_array())); });

        fcppt::variant::match(
            _variant,
            reset_pressed,
            reset_pressed,
            reset_pressed,
            [false_array, focus, this](
                fcppt::reference<sge::input::focus::event::key const> const _key_event)
            {
              fcppt::optional::maybe_void(
                  sge::input::key::to_modifier(_key_event.get().get().code()),
                  [false_array, focus, _key_event, this](sge::input::key::modifier const _mod)
                  {
                    fcppt::container::get_or_insert(
                        this->map_,
                        focus,
                        [false_array](sge::input::focus::shared_ptr const &) {
                          return false_array();
                        })[_mod] = sge::input::key::pressed{_key_event.get().pressed()};
                  });
            },
            [this, focus](fcppt::reference<sge::input::focus::event::remove const>)
            { this->map_.erase(focus); });
      });
}

sge::input::key::mod_state
sge::input::focus::mod_state_tracker::mod_state(sge::input::focus::shared_ptr const &_ref) const
{
  return fcppt::optional::maybe(
      fcppt::container::find_opt_mapped(this->map_, _ref),
      [] { return sge::input::key::mod_state::null(); },
      [](fcppt::reference<pressed_array const> const _pressed)
      {
        return fcppt::algorithm::fold(
            fcppt::enum_::make_range<sge::input::key::modifier>(),
            sge::input::key::mod_state::null(),
            [&_pressed](
                sge::input::key::modifier const _mod, sge::input::key::mod_state const _state)
            { return _pressed.get()[_mod].get() ? _state | _mod : _state; });
      });
}
