//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/projectile/scalar.hpp>
#include <sge/projectile/vector2.hpp>
#include <sge/projectile/body/object.hpp>
#include <sge/projectile/body/parameters.hpp>
#include <sge/projectile/body/position.hpp>
#include <sge/projectile/body/position_change.hpp>
#include <sge/projectile/body/rotation.hpp>
#include <sge/projectile/body/rotation_change.hpp>
#include <sge/projectile/body/user_data.hpp>
#include <sge/projectile/body/solidity/variant.hpp>
#include <sge/projectile/impl/bullet_to_vector2.hpp>
#include <sge/projectile/impl/vector2_to_bullet.hpp>
#include <sge/projectile/impl/body/detail/motion_state.hpp>
#include <sge/projectile/impl/body/solidity/extract_mass.hpp>
#include <sge/projectile/impl/body/solidity/is_solid.hpp>
#include <sge/projectile/shape/base.hpp>
#include <sge/projectile/shape/shared_base_ptr.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/verbose.hpp>
#include <fcppt/math/vector/output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/config/external_begin.hpp>
#include <BulletCollision/CollisionDispatch/btCollisionObject.h>
#include <BulletCollision/CollisionShapes/btCollisionShape.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <LinearMath/btMatrix3x3.h>
#include <LinearMath/btScalar.h>
#include <LinearMath/btTransform.h>
#include <LinearMath/btVector3.h>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace
{

btVector3 inertia_for_shape(
    fcppt::log::object &_log, // NOLINT(google-runtime-references)
    btCollisionShape &shape, // NOLINT(google-runtime-references)
    sge::projectile::body::solidity::variant const &solidity)
{
  btVector3 inertia(0, 0, 0);

  btScalar const mass = sge::projectile::impl::body::solidity::extract_mass(solidity);

  // FIXME: Rather test if the solidity actually implies a mass, then
  // do an if() on that.
  if (mass >
      static_cast<btScalar>(
          0.000001)) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  {
    FCPPT_LOG_DEBUG(
        _log,
        fcppt::log::out << FCPPT_TEXT("solid body with mass ") << mass
                        << FCPPT_TEXT(" so calculating inertia"))

    shape.calculateLocalInertia(mass, inertia);
  }

  return inertia;
}

btMatrix3x3 create_rotation_matrix(btScalar const angle)
{
  btMatrix3x3 result = btMatrix3x3::getIdentity();
  result.setEulerYPR(0, 0, angle);
  return result;
}
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::projectile::body::object::object(sge::projectile::body::parameters const &p)
    : log_{p.log()},
      transformation_(fcppt::make_unique_ptr<btTransform>(
          create_rotation_matrix(p.rotation().get()),
          sge::projectile::impl::vector2_to_bullet(p.position().get()))),
      motion_state_(fcppt::make_unique_ptr<sge::projectile::body::detail::motion_state>(
          fcppt::make_ref(*this))),
      position_change_(),
      rotation_change_(),
      shape_(p.shape()),
      body_(fcppt::make_unique_ptr<btRigidBody>(btRigidBody::btRigidBodyConstructionInfo(
          // mass
          sge::projectile::impl::body::solidity::extract_mass(p.solidity()),
          // motion state
          motion_state_.get_pointer(),
          // shape
          &(shape_->bullet_shape()),
          inertia_for_shape(log_, shape_->bullet_shape(), p.solidity())))),
      user_data_(p.user_data())
{
  FCPPT_LOG_DEBUG(
      log_,
      fcppt::log::out << this << FCPPT_TEXT(": Created a new body, position ") << p.position().get()
                      << FCPPT_TEXT(", rotation ") << p.rotation().get() << FCPPT_TEXT(", mass ")
                      << sge::projectile::impl::body::solidity::extract_mass(p.solidity())
                      << FCPPT_TEXT(", linear velocity ") << p.linear_velocity().get()
                      << FCPPT_TEXT(", angular velocity ") << p.angular_velocity().get())

  body_->forceActivationState(DISABLE_DEACTIVATION);

  body_->setUserPointer(this);

  if (!sge::projectile::impl::body::solidity::is_solid(p.solidity()))
  {
    FCPPT_LOG_DEBUG(
        log_, fcppt::log::out << this << FCPPT_TEXT(": Setting to nonsolid (no contact response)"))

    body_->setCollisionFlags(
        body_->getCollisionFlags() | // NOLINT(hicpp-signed-bitwise)
        btCollisionObject::CF_NO_CONTACT_RESPONSE);
  }

  // Constrain to 2D
  body_->setLinearFactor(
      btVector3(static_cast<btScalar>(1), static_cast<btScalar>(1), static_cast<btScalar>(0)));

  linear_velocity(p.linear_velocity().get());

  body_->setAngularFactor(
      btVector3(static_cast<btScalar>(0), static_cast<btScalar>(0), static_cast<btScalar>(1)));

  angular_velocity(p.angular_velocity().get());
}
FCPPT_PP_POP_WARNING

sge::projectile::vector2 sge::projectile::body::object::position() const
{
  return sge::projectile::impl::bullet_to_vector2(transformation_->getOrigin());
}

void sge::projectile::body::object::position(sge::projectile::vector2 const &p)
{
  FCPPT_LOG_VERBOSE(
      log_, fcppt::log::out << this << FCPPT_TEXT(": Somebody reset the body's position to ") << p)

  transformation_->setOrigin(sge::projectile::impl::vector2_to_bullet(p));
  // For speed and position calculation afterwards, it uses the
  // centerOfMassTransform and the *Interpolation* methods, so we
  // reset them here, too. It _seems_ to work at least.
  //body_->setWorldTransform(
  //	transformation_);
  body_->setCenterOfMassTransform(*transformation_);
  //body_->setInterpolationWorldTransform(
  //	*transformation_);
  // We have to re-activate a maybe-sleeping body
  body_->setActivationState(ACTIVE_TAG);
  position_change_(sge::projectile::body::position(p));
}

sge::projectile::vector2 sge::projectile::body::object::linear_velocity() const
{
  return sge::projectile::impl::bullet_to_vector2(body_->getLinearVelocity());
}

void sge::projectile::body::object::linear_velocity(vector2 const &v)
{
  FCPPT_LOG_DEBUG(
      log_,
      fcppt::log::out << this << FCPPT_TEXT(": Somebody reset the body's linear velocity to ") << v)

  body_->setLinearVelocity(sge::projectile::impl::vector2_to_bullet(v));
  // We have to re-activate a maybe-sleeping body
  body_->setActivationState(ACTIVE_TAG);
}

sge::projectile::scalar sge::projectile::body::object::angular_velocity() const
{
  return body_->getAngularVelocity().length();
}

void sge::projectile::body::object::angular_velocity(scalar const v)
{
  FCPPT_LOG_DEBUG(
      log_,
      fcppt::log::out << this << FCPPT_TEXT(": Somebody reset the body's angular velocity to ")
                      << v)

  body_->setAngularVelocity(btVector3(0, 0, v));

  // We have to re-activate a maybe-sleeping body
  body_->setActivationState(ACTIVE_TAG);
}

sge::projectile::shape::shared_base_ptr sge::projectile::body::object::shape() const
{
  return shape_;
}

sge::projectile::scalar sge::projectile::body::object::rotation() const
{
  btScalar y{};
  btScalar x{};
  btScalar z{};

  transformation_->getBasis().getEulerYPR(y, x, z);
  return z;
}

void sge::projectile::body::object::rotation(scalar const r)
{
  FCPPT_LOG_VERBOSE(
      log_, fcppt::log::out << this << FCPPT_TEXT(": Somebody reset the body's rotation to ") << r)

  transformation_->getBasis().setEulerYPR(0, 0, r);
  body_->setWorldTransform(*transformation_);
  rotation_change_(sge::projectile::body::rotation(rotation()));
}

fcppt::signal::auto_connection
sge::projectile::body::object::position_change(sge::projectile::body::position_change &&f)
{
  return position_change_.connect(std::move(f));
}

fcppt::signal::auto_connection
sge::projectile::body::object::rotation_change(sge::projectile::body::rotation_change &&f)
{
  return rotation_change_.connect(std::move(f));
}

sge::projectile::body::user_data const &sge::projectile::body::object::user_data() const
{
  return user_data_;
}

sge::projectile::body::object::~object() = default;

void sge::projectile::body::object::getWorldTransform(btTransform &t) const
{
  t = *transformation_;
}

void sge::projectile::body::object::setWorldTransform(btTransform const &t)
{
  FCPPT_LOG_VERBOSE(
      log_,
      fcppt::log::out << this << FCPPT_TEXT(": Somebody wants to reset our world transformation! "))

  (*transformation_) = t;

  FCPPT_LOG_VERBOSE(
      log_,
      fcppt::log::out << this << FCPPT_TEXT(": New position ") << this->position()
                      << FCPPT_TEXT(", rotation ") << this->rotation())

  FCPPT_LOG_VERBOSE(
      log_,
      fcppt::log::out << this << FCPPT_TEXT(": New linear velocity ") << this->linear_velocity())

  position_change_(sge::projectile::body::position(this->position()));
  rotation_change_(sge::projectile::body::rotation(this->rotation()));
}
