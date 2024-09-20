//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/graph/axis_constraint.hpp>
#include <sge/graph/baseline.hpp>
#include <sge/graph/color.hpp>
#include <sge/graph/color_scheme.hpp>
#include <sge/graph/object.hpp>
#include <sge/graph/optional_axis_constraint.hpp>
#include <sge/graph/position.hpp>
#include <sge/graph/scalar.hpp>
#include <sge/graph/impl/detail/draw_visitor.hpp>
#include <sge/image/difference_type.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image2d/vector.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/ffp.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/color_format.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/scoped_planar_lock.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single_impl.hpp> // NOLINT(misc-include-cleaner)
#include <sge/sprite/buffers/with_declaration_impl.hpp> // NOLINT(misc-include-cleaner)
#include <sge/sprite/process/one.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/state/object_impl.hpp> // NOLINT(misc-include-cleaner)
#include <sge/sprite/state/parameters_impl.hpp> // NOLINT(misc-include-cleaner)
#include <sge/texture/part_raw_ref.hpp>
#include <mizuiro/color/operators.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/const.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/cast/float_to_int_fun.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/math/clamp.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/maybe_void_multi.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/variant/apply.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace
{

// TODO(philipp): Use fcppt::math::bresenham?
template <typename View, typename Color>
void bresenham(
    View const &v,
    typename View::dim const &start,
    typename View::dim const &end,
    Color const &c0,
    Color const &c1)
{
  using int_type = std::make_signed_t<typename View::dim::value_type>;

  auto x0 = static_cast<int_type>(start[0]);
  auto y0 = static_cast<int_type>(start[1]);
  auto x1 = static_cast<int_type>(end[0]);
  auto y1 = static_cast<int_type>(end[1]);

  bool const steep = std::abs(y1 - y0) > std::abs(x1 - x0);
  if (steep)
  {
    std::swap(x0, y0);
    std::swap(x1, y1);
  }
  if (x0 > x1)
  {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }

  int_type const deltax = x1 - x0;
  int_type const deltay = std::abs(y1 - y0);
  int_type error = deltax / 2;
  int_type y = y0;
  int_type const ystep = (y0 < y1) ? 1 : -1;

  double const length = (static_cast<double>(x1 - x0) * static_cast<double>(x1 - x0)) +
                        (static_cast<double>(y1 - y0) * static_cast<double>(y1 - y0));

  for (int_type x = x0; x <= x1; ++x)
  {
    double const pos = (static_cast<double>(x - x0) * static_cast<double>(x - x0)) +
                       (static_cast<double>(y - y0) * static_cast<double>(y - y0));
    double const t = std::sqrt(pos / length);

    Color c = (t * c1) + ((1.0 - t) * c0);

    if (steep)
    {
      v[typename View::dim(
          static_cast<typename View::dim::value_type>(y),
          static_cast<typename View::dim::value_type>(x))] = c;
    }
    else
    {
      v[typename View::dim(
          static_cast<typename View::dim::value_type>(x),
          static_cast<typename View::dim::value_type>(y))] = c;
    }
    error -= deltay;
    if (error < 0)
    {
      y += ystep;
      error += deltax;
    }
  }
}

template <typename View, typename Color>
void adapted_bresenham(
    View const &_view,
    sge::image2d::vector const &_pos1,
    sge::image2d::vector const &_pos2,
    Color const &_color1,
    Color const &_color2)
{
  ::bresenham(
      _view,
      typename View::dim(_pos1.x(), _pos1.y()),
      typename View::dim(_pos2.x(), _pos2.y()),
      sge::image::color::any::convert<typename View::format::color_format>(
          sge::image::color::any::object{_color1}),
      sge::image::color::any::convert<typename View::format::color_format>(
          sge::image::color::any::object{_color2}));
}

sge::graph::scalar
normalize(sge::graph::scalar const &t, sge::graph::scalar const &min, sge::graph::scalar const &max)
{
  if (min >= max)
  {
    return 0.;
  }
  return (t - min) / (max - min);
}

template <typename View>
void draw_rectangle(
    View const &_view,
    sge::image2d::vector const &_corner1,
    sge::image2d::vector const &_corner2,
    sge::graph::color const &_color)
{
  adapted_bresenham(
      _view, _corner1, sge::image2d::vector(_corner1.x(), _corner2.y()), _color, _color);
  adapted_bresenham(
      _view, _corner1, sge::image2d::vector(_corner2.x(), _corner1.y()), _color, _color);
  adapted_bresenham(
      _view, sge::image2d::vector(_corner1.x(), _corner2.y()), _corner2, _color, _color);
  adapted_bresenham(
      _view, sge::image2d::vector(_corner2.x(), _corner1.y()), _corner2, _color, _color);
}

fcppt::optional::object<sge::image2d::vector::value_type> fit_into_scale(
    sge::graph::scalar const _value,
    sge::graph::scalar const _min,
    sge::graph::scalar const _max,
    sge::renderer::dim2::value_type const _height)
{
  return fcppt::optional::map(
      fcppt::math::clamp(
          fcppt::cast::int_to_float<sge::graph::scalar>(_height - 1) *
              (1.0 - normalize(_value, _min, _max)),
          0.0,
          fcppt::cast::int_to_float<sge::graph::scalar>(_height - 1)),
      [](sge::graph::scalar const _clamped)
      {
        return fcppt::cast::to_unsigned(
            fcppt::cast::float_to_int<sge::image::difference_type>(_clamped));
      });
}

}

sge::graph::object::object(
    sge::graph::position const &_position,
    sge::renderer::dim2 const &_dim,
    sge::renderer::device::ffp_ref const _renderer,
    sge::graph::baseline _baseline,
    sge::graph::optional_axis_constraint const &_axis_constraint,
    sge::graph::color_scheme const &_color_scheme)
    : dim_(_dim),
      texture_(_renderer.get().create_planar_texture(sge::renderer::texture::planar_parameters(
          _dim,
          sge::renderer::texture::color_format(
              sge::image::color::format::rgba8, sge::renderer::texture::emulate_srgb::no),
          sge::renderer::texture::mipmap::off(),
          sge::renderer::resource_flags_field::null(),
          sge::renderer::texture::capabilities_field::null()))),
      sprite_object_{
          sge::sprite::roles::pos{} = fcppt::math::vector::
              structure_cast<sprite_object::vector, fcppt::cast::float_to_int_fun>(_position.get()),
          sge::sprite::roles::texture0{} =
              sprite_object::texture_type{
                  fcppt::make_shared_ptr<sge::texture::part_raw_ref>(*texture_)}},
      sprite_buffers_(
          fcppt::reference_to_base<sge::renderer::device::core>(_renderer),
          sge::sprite::buffers::option::dynamic),
      sprite_state_(_renderer, sprite_state_parameters()),
      data_buffer_(dim_.w()),
      baseline_(_baseline.get()),
      color_scheme_(_color_scheme),
      axis_constraint_(_axis_constraint),
      current_min_(std::min(0., baseline_)),
      current_max_(1. + std::max(current_min_, baseline_))
{
  sge::renderer::texture::scoped_planar_lock const lock(
      fcppt::make_ref(*texture_), sge::renderer::lock_mode::writeonly);

  fcppt::variant::apply(
      sge::graph::detail::draw_visitor(fcppt::make_ref(*this)), lock.value().get());
}

void sge::graph::object::push(sge::graph::scalar const _datum)
{
  data_buffer_.push_back(_datum);

  current_min_ = std::min(current_min_, _datum);

  current_max_ = std::max(current_max_, _datum);

  if (current_max_ <= current_min_)
  {
    current_max_ += 1.0;
  }
}

void sge::graph::object::render(sge::renderer::context::ffp &_context)
{
  {
    sge::renderer::texture::scoped_planar_lock const lock(
        fcppt::make_ref(*texture_), sge::renderer::lock_mode::writeonly);

    fcppt::variant::apply(
        sge::graph::detail::draw_visitor(fcppt::make_ref(*this)), lock.value().get());
  }

  sge::sprite::process::one(_context, sprite_object_, sprite_buffers_, sprite_state_);
}

template <typename View>
void sge::graph::object::clear(View const &_view)
{
  for (sge::image::size_type const x : fcppt::make_int_range_count(dim_.w()))
  {
    adapted_bresenham(
        _view,
        sge::image2d::vector(x, 0U),
        sge::image2d::vector(x, dim_.h() - 1U),
        color_scheme_.background_color(),
        color_scheme_.background_alt_color());
  }

  draw_rectangle(
      _view,
      sge::image2d::vector(0U, 0U),
      sge::image2d::vector(dim_.w() - 1U, dim_.h() - 1U),
      color_scheme_.foreground_alt_color());
}

template <typename View>
void sge::graph::object::draw_data(View const &_view)
{
  this->clear(_view);

  sge::graph::axis_constraint const current_axis_constraint{
      sge::graph::axis_constraint::min_type{fcppt::optional::maybe(
          axis_constraint_,
          fcppt::const_(current_min_),
          [](sge::graph::axis_constraint const _cur) { return _cur.min(); })},
      sge::graph::axis_constraint::max_type{fcppt::optional::maybe(
          axis_constraint_,
          fcppt::const_(current_max_),
          [](sge::graph::axis_constraint const _cur) { return _cur.max(); })}};

  using value_type = sge::image2d::vector::value_type;

  fcppt::optional::maybe_void_multi(
      [this, &_view, &current_axis_constraint](value_type const _baseline, value_type const _zero)
      {
        for (auto const index : fcppt::make_int_range_count(this->data_buffer_.size()))
        {
          sge::graph::scalar const cur{this->data_buffer_[index]};

          fcppt::optional::maybe_void(
              fcppt::math::clamp(cur, current_axis_constraint.min(), current_axis_constraint.max()),
              [this, cur, &_view, index, _zero, &current_axis_constraint](
                  sge::graph::scalar const _clamped)
              {
                fcppt::optional::maybe_void(
                    fit_into_scale(
                        _clamped,
                        current_axis_constraint.min(),
                        current_axis_constraint.max(),
                        this->dim_.h()),
                    [this, cur, &_view, index, _zero](value_type const _value)
                    {
                      bool const above{cur > 0.0};

                      sge::graph::color const &col1{
                          above ? this->color_scheme_.foreground_color()
                                : this->color_scheme_.foreground_alt_color()};

                      sge::graph::color const &col2{
                          above ? this->color_scheme_.foreground_alt_color()
                                : this->color_scheme_.foreground_color()};

                      adapted_bresenham(
                          _view,
                          sge::image2d::vector(index, _zero),
                          sge::image2d::vector(index, _value),
                          col1,
                          col2);
                    });
              });
        }

        // zero line
        adapted_bresenham(
            _view,
            sge::image2d::vector(0U, _zero),
            sge::image2d::vector(dim_.w() - 1U, _zero),
            color_scheme_.foreground_alt_color(),
            color_scheme_.foreground_alt_color());

        // baseline
        adapted_bresenham(
            _view,
            sge::image2d::vector(0U, _baseline),
            sge::image2d::vector(dim_.w() - 1U, _baseline),
            color_scheme_.baseline_color(),
            color_scheme_.baseline_color());
      },
      fit_into_scale(
          this->baseline_,
          current_axis_constraint.min(),
          current_axis_constraint.max(),
          this->dim_.h()),
      fit_into_scale(
          0.0, current_axis_constraint.min(), current_axis_constraint.max(), this->dim_.h()));
}

sge::graph::object::~object() = default;
