//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/object_ref.hpp>
#include <sge/font/string.hpp>
#include <sge/gui/click_callback.hpp>
#include <sge/gui/context_ref.hpp>
#include <sge/gui/optional_needed_width.hpp>
#include <sge/gui/impl/relayout_ancestor.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/button.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/gui/widget/reference_alignment_vector.hpp>
#include <sge/gui/widget/reference_name_pair.hpp>
#include <sge/gui/widget/reference_name_vector.hpp>
#include <sge/gui/widget/tab.hpp>
#include <sge/gui/widget/unique_ptr.hpp>
#include <sge/gui/widget/unique_ptr_vector.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/container/maybe_front.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::gui::widget::tab::tab(
    sge::gui::context_ref const _context,
    sge::gui::style::const_reference const _style,
    sge::renderer::device::ffp_ref const _renderer,
    sge::font::object_ref const _font,
    sge::gui::widget::reference_name_vector const &_widgets)
    : sge::gui::widget::box_container(
          _context, sge::gui::widget::reference_alignment_vector(), sge::rucksack::axis::y),
      top_buttons_(fcppt::algorithm::map<sge::gui::widget::unique_ptr_vector>(
          _widgets,
          [&_style, &_renderer, &_font, this](sge::gui::widget::reference_name_pair const &_pair)
          {
            class gui_button : public sge::gui::widget::button
            {
              FCPPT_NONMOVABLE(gui_button);

            public:
              gui_button(
                  sge::gui::style::const_reference const _style_arg,
                  sge::renderer::device::ffp_ref const _renderer_arg,
                  sge::font::object_ref const _font_arg,
                  sge::font::string const &_name,
                  sge::gui::widget::reference const _widget,
                  fcppt::reference<sge::gui::widget::tab> const _self)
                  : sge::gui::widget::button(
                        _style_arg,
                        _renderer_arg,
                        _font_arg,
                        _name,
                        sge::gui::optional_needed_width()),
                    click_connection_(this->click(sge::gui::click_callback{
                        [_widget, _self]()
                        {
                          _self.get().replace(
                              1U,
                              sge::gui::widget::reference_alignment_pair(
                                  _widget, sge::rucksack::alignment::left_or_top));

                          sge::gui::impl::relayout_ancestor(_self.get());
                        }}))
              {
              }

              ~gui_button() override = default;

            private:
              fcppt::signal::auto_connection const click_connection_;
            };

            return fcppt::unique_ptr_to_base<
                sge::gui::widget::base>(fcppt::make_unique_ptr<gui_button>(
                _style, _renderer, _font, _pair.name(), _pair.reference(), fcppt::make_ref(*this)));
          })),
      top_buttons_box_(
          _context,
          fcppt::algorithm::map<sge::gui::widget::reference_alignment_vector>(
              top_buttons_,
              [](sge::gui::widget::unique_ptr const &_widget)
              {
                return sge::gui::widget::reference_alignment_pair(
                    sge::gui::widget::reference(*_widget), sge::rucksack::alignment::left_or_top);
              }),
          sge::rucksack::axis::x)
{
  this->push_back(sge::gui::widget::reference_alignment_pair(
      sge::gui::widget::reference(top_buttons_box_), sge::rucksack::alignment::left_or_top));

  fcppt::optional::maybe_void(
      fcppt::container::maybe_front(_widgets),
      [this](fcppt::reference<sge::gui::widget::reference_name_pair const> const _front)
      {
        this->push_back(sge::gui::widget::reference_alignment_pair(
            _front.get().reference(), sge::rucksack::alignment::left_or_top));
      });
}

FCPPT_PP_POP_WARNING

sge::gui::widget::tab::~tab() = default;
