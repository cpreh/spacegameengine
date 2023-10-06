//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PROJECTILE_IMPL_COLLISION_TESTER_HPP_INCLUDED
#define SGE_PROJECTILE_IMPL_COLLISION_TESTER_HPP_INCLUDED

#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <BulletCollision/CollisionDispatch/btCollisionWorld.h>
#include <LinearMath/btScalar.h>
#include <fcppt/config/external_end.hpp>

struct btCollisionObjectWrapper;
struct btBroadphaseProxy;
class btManifoldPoint;

namespace sge::projectile::impl
{

class collision_tester : public btCollisionWorld::ContactResultCallback
{
  FCPPT_NONMOVABLE(collision_tester);

public:
  collision_tester();

  ~collision_tester() override;

  [[nodiscard]] bool result() const;

private:
  [[nodiscard]] bool needsCollision(btBroadphaseProxy *) const override;

  [[nodiscard]] btScalar addSingleResult(
      btManifoldPoint &,
      btCollisionObjectWrapper const *colObj0Wrap,
      int partId0,
      int index0,
      btCollisionObjectWrapper const *colObj1Wrap,
      int partId1,
      int index1) override;

  bool result_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)
};

}

#endif
