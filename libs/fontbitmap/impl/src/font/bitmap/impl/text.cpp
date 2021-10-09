//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/dim.hpp>
#include <sge/font/index.hpp>
#include <sge/font/optional_index.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/view.hpp>
#include <sge/font/align_h/center.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/right.hpp>
#include <sge/font/bitmap/impl/char_map.hpp>
#include <sge/font/bitmap/impl/char_metric.hpp>
#include <sge/font/bitmap/impl/char_metric_ref.hpp>
#include <sge/font/bitmap/impl/const_view.hpp>
#include <sge/font/bitmap/impl/line.hpp>
#include <sge/font/bitmap/impl/line_height.hpp>
#include <sge/font/bitmap/impl/make_rep.hpp>
#include <sge/font/bitmap/impl/position.hpp>
#include <sge/font/bitmap/impl/text.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/any/clear.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image2d/rect.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/algorithm/fill.hpp>
#include <sge/image2d/view/format.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/image2d/view/sub.hpp>
#include <fcppt/loop.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/math/box/contains_point.hpp>
#include <fcppt/math/box/null.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/to_signed.hpp>
#include <fcppt/math/dim/to_unsigned.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/to_unsigned.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/variant/match.hpp>

sge::font::bitmap::impl::text::text(
    fcppt::log::object &_log,
    sge::font::bitmap::impl::char_map const &_char_map,
    sge::font::string const &_string,
    sge::font::text_parameters const &_text_parameters,
    sge::font::bitmap::impl::line_height const _line_height)
    : line_height_(_line_height),
      align_h_(_text_parameters.align_h()),
      rep_(sge::font::bitmap::impl::make_rep(
          _log, _char_map, _line_height, _string, _text_parameters))
{
}

sge::font::bitmap::impl::text::~text() = default;

void sge::font::bitmap::impl::text::render(sge::font::view const &_view)
{
  sge::image2d::algorithm::fill(
      sge::image2d::view::sub(
          _view,
          sge::image2d::rect(
              fcppt::math::vector::null<sge::image2d::rect::vector>(),
              fcppt::math::dim::structure_cast<sge::image2d::rect::dim, fcppt::cast::size_fun>(
                  fcppt::math::dim::to_unsigned(rep_.rect().size())))),
      sge::image::color::any::clear(sge::image2d::view::format(_view)),
      sge::image::algorithm::uninitialized::yes);

  this->iterate(
      [&_view](sge::font::bitmap::impl::position const &_position)
      {
        sge::font::bitmap::impl::char_metric const &char_metric(_position.metric());

        sge::font::bitmap::impl::const_view const source_view(char_metric.view());

        sge::image2d::algorithm::copy_and_convert(
            source_view,
            sge::image2d::view::sub(
                _view,
                sge::image2d::rect(
                    fcppt::math::vector::
                        structure_cast<sge::image2d::rect::vector, fcppt::cast::size_fun>(
                            fcppt::math::vector::to_unsigned(_position.pos())),
                    sge::image2d::view::size(source_view))),
            sge::image::algorithm::may_overlap::no,
            sge::image::algorithm::uninitialized::no);

        return fcppt::loop::continue_;
      });
}

sge::font::rect sge::font::bitmap::impl::text::rect() const { return rep_.rect(); }

sge::font::dim sge::font::bitmap::impl::text::logical_size() const { return this->rect().size(); }

sge::font::rect sge::font::bitmap::impl::text::cursor_rect(sge::font::index const _index) const
{
  // TODO(philipp): This code would better be expressed using ranges.

  using optional_rect = fcppt::optional::object<sge::font::rect>;

  optional_rect result;

  sge::font::index index{0U};

  this->iterate(
      [&result, &index, _index](sge::font::bitmap::impl::position const &_position)
      {
        if (index == _index)
        {
          result = optional_rect{sge::font::rect{
              _position.pos(),
              fcppt::math::dim::structure_cast<sge::font::dim, fcppt::cast::size_fun>(
                  fcppt::math::dim::to_signed(
                      sge::image2d::view::size(_position.metric().view())))}};

          return fcppt::loop::break_;
        }

        ++index;

        return fcppt::loop::continue_;
      });

  return FCPPT_ASSERT_OPTIONAL_ERROR(result);
}

sge::font::optional_index
sge::font::bitmap::impl::text::pos_to_index(sge::font::vector const _pos) const
{
  // TODO(philipp): This code would better be expressed using ranges.

  sge::font::optional_index result;

  sge::font::index index{0U};

  this->iterate(
      [&result, &index, _pos](sge::font::bitmap::impl::position const &_position)
      {
        if (fcppt::math::box::contains_point(
                sge::font::rect{
                    _position.pos(),
                    fcppt::math::dim::structure_cast<sge::font::dim, fcppt::cast::size_fun>(
                        fcppt::math::dim::to_signed(
                            sge::image2d::view::size(_position.metric().view())))},
                _pos))
        {
          result = sge::font::optional_index{index};

          return fcppt::loop::break_;
        }

        ++index;

        return fcppt::loop::continue_;
      });

  return result;
}

template <typename Function>
void sge::font::bitmap::impl::text::iterate(Function const &_function) const
{
  sge::font::unit top(0U);

  for (sge::font::bitmap::impl::line const &line : rep_.lines())
  {
    sge::font::unit left(fcppt::variant::match(
        align_h_,
        [](sge::font::align_h::left const &) { return 0; },
        [&line, this](sge::font::align_h::center const &)
        { return (this->logical_size().w() - line.width()) / 2; },
        [&line, this](sge::font::align_h::right const &)
        { return this->logical_size().w() - line.width(); }));

    for (sge::font::bitmap::impl::char_metric_ref const &metric : line.char_metrics())
    {
      switch (_function(sge::font::bitmap::impl::position{sge::font::vector{left, top}, metric}))
      {
      case fcppt::loop::break_:
        return;
      case fcppt::loop::continue_:
        break;
      }

      left += metric.get().x_advance();
    }

    top += line_height_.get();
  }
}
