//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/camera/base.hpp>
#include <sge/camera/exception.hpp>
#include <sge/camera/has_mutable_projection.hpp>
#include <sge/camera/is_dynamic.hpp>
#include <sge/camera/optional_projection_matrix.hpp>
#include <sge/camera/update_duration.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/camera/matrix_conversion/world_matrix_to_coordinate_system.hpp>
#include <sge/camera/tracking/is_looping.hpp>
#include <sge/camera/tracking/keyframe_sequence.hpp>
#include <sge/camera/tracking/object.hpp>
#include <sge/camera/tracking/alexa/lerp.hpp>
#include <sge/input/event_base_fwd.hpp>
#include <fcppt/cyclic_iterator_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/container/maybe_front.hpp>
#include <fcppt/math/matrix/identity.hpp>
#include <fcppt/math/matrix/output.hpp>
#include <fcppt/math/matrix/static.hpp>
#include <fcppt/math/matrix/structure_cast.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/tuple/get.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace
{

sge::renderer::matrix4 lerp_double(
    sge::renderer::scalar const _t,
    sge::renderer::matrix4 const &_a,
    sge::renderer::matrix4 const &_b)
{
  using real = long double;

  using real_matrix = fcppt::math::matrix::static_<real, 4, 4>;

  return fcppt::math::matrix::structure_cast<sge::renderer::matrix4, fcppt::cast::size_fun>(
      sge::camera::tracking::alexa::lerp(
          fcppt::cast::size<real>(_t),
          fcppt::math::matrix::structure_cast<real_matrix, fcppt::cast::size_fun>(_a),
          fcppt::math::matrix::structure_cast<real_matrix, fcppt::cast::size_fun>(_b)));
}
}

sge::camera::tracking::object::object(
    sge::camera::optional_projection_matrix const _projection_matrix,
    sge::camera::tracking::keyframe_sequence &&_keyframes,
    sge::camera::tracking::is_looping const _is_looping)
    : sge::camera::base{},
      sge::camera::is_dynamic{},
      sge::camera::has_mutable_projection{},
      projection_matrix_{_projection_matrix},
      keyframes_{std::move(_keyframes)},
      is_looping_{_is_looping},
      current_keyframe_{
          keyframes_.begin(), cyclic_iterator::boundary{keyframes_.begin(), keyframes_.end()}},
      current_time_point_{0.0F},
      coordinate_system_{fcppt::optional::to_exception(
                             fcppt::container::maybe_front(keyframes_),
                             [] { return sge::camera::exception{FCPPT_TEXT("Empty keyframes!")}; })
                             .get()
                             .coordinate_system()},
      finished_{false}
{
}

sge::camera::coordinate_system::object sge::camera::tracking::object::coordinate_system() const
{
  return coordinate_system_;
}

sge::camera::optional_projection_matrix sge::camera::tracking::object::projection_matrix() const
{
  return projection_matrix_;
}

void sge::camera::tracking::object::update_projection_matrix(
    sge::camera::optional_projection_matrix const &_projection_matrix)
{
  projection_matrix_ = _projection_matrix;
}

void sge::camera::tracking::object::update(sge::camera::update_duration const _duration)
{
  current_time_point_ += _duration;

  while (current_time_point_ > current_keyframe_->duration())
  {
    current_time_point_ -= current_keyframe_->duration();

    ++current_keyframe_;

    if (current_keyframe_.get() == fcppt::tuple::get<0U>(current_keyframe_.get_boundary()))
    {
      finished_ = true;

      if (!is_looping_.get())
      {
        coordinate_system_ = keyframes_.back().coordinate_system();

        return;
      }
    }
  }

  sge::renderer::matrix4 const left{
      sge::camera::matrix_conversion::world(current_keyframe_->coordinate_system())};

  sge::renderer::matrix4 const right{
      sge::camera::matrix_conversion::world(std::next(current_keyframe_)->coordinate_system())};

  coordinate_system_ = sge::camera::matrix_conversion::world_matrix_to_coordinate_system(
      lerp_double(
          current_time_point_.count() / current_keyframe_->duration().count(),
          fcppt::math::matrix::identity<sge::renderer::matrix4>(),
          right * fcppt::math::matrix::inverse(left)) *
      left);
}

void sge::camera::tracking::object::process_event(sge::input::event_base const &) {}

bool sge::camera::tracking::object::finished() const { return finished_; }

sge::camera::tracking::object::~object() = default;
