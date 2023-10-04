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
#include <sge/camera/impl/set_pressed_if_appropriate.hpp>
#include <sge/camera/spherical/object.hpp>
#include <sge/camera/spherical/parameters.hpp>
#include <sge/camera/spherical/coordinate_system/azimuth.hpp>
#include <sge/camera/spherical/coordinate_system/inclination.hpp>
#include <sge/camera/spherical/coordinate_system/null.hpp>
#include <sge/camera/spherical/coordinate_system/radius.hpp>
#include <sge/camera/spherical/coordinate_system/to_camera_coordinate_system.hpp>
#include <sge/input/event_base.hpp>
#include <sge/input/keyboard/event/key.hpp>
#include <sge/renderer/scalar.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/math/clamp.hpp>
#include <fcppt/math/matrix/vector.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/math/vector/arithmetic.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <numbers>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::camera::spherical::object::object(sge::camera::spherical::parameters const &_params)
    : sge::camera::base{},
      sge::camera::is_dynamic{},
      sge::camera::has_mutable_projection{},
      action_mapping_{_params.action_mapping()},
      movement_speed_{_params.movement_speed()},
      origin_{_params.origin()},
      minimum_radius_{_params.minimum_radius()},
      maximum_radius_{_params.maximum_radius()},
      acceleration_factor_{_params.acceleration_factor()},
      damping_factor_{_params.damping_factor()},
      coordinate_system_{_params.coordinate_system()},
      projection_matrix_{_params.projection_matrix()},
      acceleration_{sge::camera::spherical::coordinate_system::null()},
      velocity_{sge::camera::spherical::coordinate_system::null()},
      increase_azimuth_pressed_{false},
      decrease_azimuth_pressed_{false},
      increase_inclination_pressed_{false},
      decrease_inclination_pressed_{false},
      increase_radius_pressed_{false},
      decrease_radius_pressed_{false}
{
}

FCPPT_PP_POP_WARNING

sge::camera::coordinate_system::object sge::camera::spherical::object::coordinate_system() const
{
  return fcppt::optional::to_exception(
      sge::camera::spherical::coordinate_system::to_camera_coordinate_system(
          coordinate_system_, origin_),
      [] { return sge::camera::exception{FCPPT_TEXT("Broken spherical coordinate system!")}; });
}

sge::camera::optional_projection_matrix sge::camera::spherical::object::projection_matrix() const
{
  return projection_matrix_;
}

void sge::camera::spherical::object::update_projection_matrix(
    sge::camera::optional_projection_matrix const &_projection_matrix)
{
  projection_matrix_ = _projection_matrix;
}

void sge::camera::spherical::object::update(sge::camera::update_duration const _time_delta)
{
  velocity_.azimuth(
      sge::camera::spherical::coordinate_system::azimuth(
          1.0F - (1.0F - damping_factor_.get().azimuth().get()) * _time_delta.count()) *
      (velocity_.azimuth() +
       acceleration_factor_.get().azimuth() * acceleration_.azimuth() *
           sge::camera::spherical::coordinate_system::azimuth(_time_delta.count())));

  velocity_.inclination(
      sge::camera::spherical::coordinate_system::inclination(
          1.0F - (1.0F - damping_factor_.get().inclination().get()) * _time_delta.count()) *
      (velocity_.inclination() +
       acceleration_factor_.get().inclination() * acceleration_.inclination() *
           sge::camera::spherical::coordinate_system::inclination(_time_delta.count())));

  velocity_.radius(
      sge::camera::spherical::coordinate_system::radius(
          1.0F - (1.0F - damping_factor_.get().radius().get()) * _time_delta.count()) *
      (velocity_.radius() +
       acceleration_factor_.get().radius() * acceleration_.radius() *
           sge::camera::spherical::coordinate_system::radius(_time_delta.count())));

  fcppt::optional::maybe_void(
      fcppt::math::clamp(
          coordinate_system_.radius().get() +
              _time_delta.count() * movement_speed_.get().radius().get() * velocity_.radius().get(),
          minimum_radius_.get(),
          maximum_radius_.get()),
      [this](sge::renderer::scalar const _radius) {
        this->coordinate_system_.radius(sge::camera::spherical::coordinate_system::radius(_radius));
      });

  coordinate_system_.azimuth(sge::camera::spherical::coordinate_system::azimuth(
      coordinate_system_.azimuth().get() +
      _time_delta.count() * movement_speed_.get().azimuth().get() * velocity_.azimuth().get()));

  constexpr sge::renderer::scalar const inclination_epsilon{0.01F};

  fcppt::optional::maybe_void(
      fcppt::math::clamp(
          coordinate_system_.inclination().get() + _time_delta.count() *
                                                       movement_speed_.get().inclination().get() *
                                                       velocity_.inclination().get(),
          -std::numbers::pi_v<sge::renderer::scalar> + inclination_epsilon,
          -inclination_epsilon),
      [this](sge::renderer::scalar const _inclination)
      {
        this->coordinate_system_.inclination(
            sge::camera::spherical::coordinate_system::inclination{_inclination});
      });
}

void sge::camera::spherical::object::process_event(sge::input::event_base const &_event)
{
  fcppt::optional::maybe_void(
      fcppt::cast::dynamic<sge::input::keyboard::event::key const>(_event),
      [this](fcppt::reference<sge::input::keyboard::event::key const> const _key_event)
      { this->key_event(_key_event.get()); });
}

sge::camera::spherical::object::~object() = default;

namespace
{

sge::renderer::scalar direction_from_booleans(bool const _left, bool const _right)
{
  return _left && !_right ? -1.0F : _right && !_left ? 1.0F : 0.0F;
}

}

void sge::camera::spherical::object::key_event(sge::input::keyboard::event::key const &_key_event)
{
  sge::camera::impl::set_pressed_if_appropriate(
      fcppt::make_ref(increase_azimuth_pressed_),
      action_mapping_.increase_azimuth().get(),
      _key_event);

  sge::camera::impl::set_pressed_if_appropriate(
      fcppt::make_ref(decrease_azimuth_pressed_),
      action_mapping_.decrease_azimuth().get(),
      _key_event);

  sge::camera::impl::set_pressed_if_appropriate(
      fcppt::make_ref(increase_inclination_pressed_),
      action_mapping_.increase_inclination().get(),
      _key_event);

  sge::camera::impl::set_pressed_if_appropriate(
      fcppt::make_ref(decrease_inclination_pressed_),
      action_mapping_.decrease_inclination().get(),
      _key_event);

  sge::camera::impl::set_pressed_if_appropriate(
      fcppt::make_ref(increase_radius_pressed_),
      action_mapping_.increase_radius().get(),
      _key_event);

  sge::camera::impl::set_pressed_if_appropriate(
      fcppt::make_ref(decrease_radius_pressed_),
      action_mapping_.decrease_radius().get(),
      _key_event);

  acceleration_.azimuth(sge::camera::spherical::coordinate_system::azimuth(
      direction_from_booleans(increase_azimuth_pressed_, decrease_azimuth_pressed_)));

  acceleration_.inclination(sge::camera::spherical::coordinate_system::inclination(
      direction_from_booleans(increase_inclination_pressed_, decrease_inclination_pressed_)));

  acceleration_.radius(sge::camera::spherical::coordinate_system::radius(
      direction_from_booleans(increase_radius_pressed_, decrease_radius_pressed_)));
}
