//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/projectile/log.hpp>
#include <sge/projectile/body/angular_velocity.hpp>
#include <sge/projectile/body/linear_velocity.hpp>
#include <sge/projectile/body/parameters.hpp>
#include <sge/projectile/body/position.hpp>
#include <sge/projectile/body/rotation.hpp>
#include <sge/projectile/body/user_data.hpp>
#include <sge/projectile/body/solidity/variant.hpp>
#include <sge/projectile/shape/shared_base_ptr.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::projectile::body::parameters::parameters(
    sge::projectile::log const &_log,
    sge::projectile::body::position const _position,
    sge::projectile::body::linear_velocity const _linear_velocity,
    sge::projectile::body::angular_velocity const &_angular_velocity,
    sge::projectile::shape::shared_base_ptr _shape,
    sge::projectile::body::rotation const &_rotation,
    sge::projectile::body::solidity::variant const &_solidity,
    sge::projectile::body::user_data _user_data)
    : log_{_log.body_log()},
      position_(_position),
      linear_velocity_(_linear_velocity),
      angular_velocity_(_angular_velocity),
      shape_(std::move(_shape)),
      rotation_(_rotation),
      solidity_(_solidity),
      user_data_(std::move(_user_data))
{
}

fcppt::log::object &sge::projectile::body::parameters::log() const { return log_.get(); }

sge::projectile::body::position const &sge::projectile::body::parameters::position() const
{
  return position_;
}

sge::projectile::body::linear_velocity const &
sge::projectile::body::parameters::linear_velocity() const
{
  return linear_velocity_;
}

sge::projectile::body::angular_velocity const &
sge::projectile::body::parameters::angular_velocity() const
{
  return angular_velocity_;
}

sge::projectile::shape::shared_base_ptr const &sge::projectile::body::parameters::shape() const
{
  return shape_;
}

sge::projectile::body::rotation const &sge::projectile::body::parameters::rotation() const
{
  return rotation_;
}

sge::projectile::body::solidity::variant const &sge::projectile::body::parameters::solidity() const
{
  return solidity_;
}

sge::projectile::body::user_data const &sge::projectile::body::parameters::user_data() const
{
  return user_data_;
}
