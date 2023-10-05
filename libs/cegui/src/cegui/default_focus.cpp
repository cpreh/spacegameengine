//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cegui/default_focus.hpp>
#include <sge/cegui/syringe.hpp> // NOLINT(misc-include-cleaner)
#include <sge/cegui/syringe_ref.hpp>
#include <sge/input/event_base.hpp>
#include <sge/input/focus/event/key.hpp>
#include <sge/input/focus/event/key_repeat.hpp>
#include <sge/input/focus/event/text.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>

sge::cegui::default_focus::default_focus(sge::cegui::syringe_ref const _syringe)
    : syringe_{_syringe}
{
}

sge::cegui::default_focus::~default_focus() = default;

void sge::cegui::default_focus::process_event(sge::input::event_base const &_event)
{
  fcppt::optional::maybe_void(
      fcppt::variant::dynamic_cast_<
          fcppt::mpl::list::object<
              sge::input::focus::event::key const,
              sge::input::focus::event::key_repeat const,
              sge::input::focus::event::text const>,
          fcppt::cast::dynamic_fun>(_event),
      [this](auto const &_variant)
      {
        fcppt::variant::match(
            _variant,
            [this](fcppt::reference<sge::input::focus::event::key const> const _key_event)
            { this->syringe_.get().inject(_key_event.get()); },
            [this](fcppt::reference<sge::input::focus::event::key_repeat const> const
                       _key_repeat_event) { this->syringe_.get().inject(_key_repeat_event.get()); },
            [this](fcppt::reference<sge::input::focus::event::text const> const _text_event)
            { this->syringe_.get().inject(_text_event.get()); });
      });
}
