//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/projectile/exception.hpp>
#include <sge/projectile/body/object.hpp>
#include <sge/projectile/ghost/object.hpp>
#include <sge/projectile/impl/ghost/detail/pair_callback.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <BulletCollision/BroadphaseCollision/btBroadphaseProxy.h>
#include <BulletCollision/CollisionDispatch/btCollisionObject.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <fcppt/config/external_end.hpp>

sge::projectile::ghost::detail::pair_callback::pair_callback() = default;

sge::projectile::ghost::detail::pair_callback::~pair_callback() = default;

btBroadphasePair *sge::projectile::ghost::detail::pair_callback::addOverlappingPair(
    btBroadphaseProxy *proxy0, btBroadphaseProxy *proxy1)
{
  auto *col_obj0{static_cast<btCollisionObject *>(proxy0->m_clientObject)};

  auto *col_obj1{static_cast<btCollisionObject *>(proxy1->m_clientObject)};

  btGhostObject *ghost0{btGhostObject::upcast(col_obj0)};

  btGhostObject *ghost1{btGhostObject::upcast(col_obj1)};

  // FIXME: ASSERT
  if (ghost0 != nullptr)
  {
    if (ghost1 == nullptr)
    {
      if(ghost0->getUserPointer() == nullptr)
      {
        throw sge::projectile::exception{FCPPT_TEXT("ghost0 has no user pointer!")};
      }
      void *user_pointer0 = ghost0->getUserPointer();
      if(col_obj1 == nullptr)
      {
        throw sge::projectile::exception{FCPPT_TEXT("Collision object1 is null!")};
      }
      if(col_obj1->getUserPointer() == nullptr)
      {
        throw sge::projectile::exception{FCPPT_TEXT("Collision object1 has no user pointer!")};
      }
      void *user_pointer1 = col_obj1->getUserPointer();

      fcppt::cast::from_void_ptr<object *>(user_pointer0)
          ->enter_internal(*fcppt::cast::from_void_ptr<body::object const *>(user_pointer1));
    }
    ghost0->addOverlappingObjectInternal(proxy1, proxy0);
  }

  if (ghost1 != nullptr)
  {
    if (ghost0 == nullptr)
    {
      if(ghost1->getUserPointer() == nullptr)
      {
        throw sge::projectile::exception{FCPPT_TEXT("ghost1 has no user pointer!")};
      }
      void *user_pointer1 = ghost1->getUserPointer();
      if(col_obj0 == nullptr)
      {
        throw sge::projectile::exception{FCPPT_TEXT("Collision object0 is null!")};
      }
      if(col_obj0->getUserPointer() == nullptr)
      {
        throw sge::projectile::exception{FCPPT_TEXT("Collision object0 has no user pointer!")};
      }
      void *user_pointer0 = col_obj0->getUserPointer();

      fcppt::cast::from_void_ptr<object *>(user_pointer1)
          ->enter_internal(*fcppt::cast::from_void_ptr<body::object const *>(user_pointer0));
    }

    ghost1->addOverlappingObjectInternal(proxy0, proxy1);
  }

  return nullptr;
}

void *sge::projectile::ghost::detail::pair_callback::removeOverlappingPair(
    btBroadphaseProxy *proxy0, btBroadphaseProxy *proxy1, btDispatcher *dispatcher)
{
  btCollisionObject *col_obj0{static_cast<btCollisionObject *>(proxy0->m_clientObject)};

  btCollisionObject *col_obj1{static_cast<btCollisionObject *>(proxy1->m_clientObject)};

  btGhostObject *ghost0{btGhostObject::upcast(col_obj0)};

  btGhostObject *ghost1{btGhostObject::upcast(col_obj1)};

  if (ghost0 != nullptr)
  {
    if (ghost1 == nullptr)
    {
      if(ghost0->getUserPointer() == nullptr)
      {
        throw sge::projectile::exception{FCPPT_TEXT("ghost0 has no user pointer!")};
      }
      void *user_pointer0 = ghost0->getUserPointer();
      if(col_obj1 == nullptr)
      {
        throw sge::projectile::exception{FCPPT_TEXT("Collision object1 is null!")};
      }
      if(col_obj1->getUserPointer() == nullptr)
      {
        throw sge::projectile::exception{FCPPT_TEXT("Collision object1 has no user pointer!")};
      }
      void *user_pointer1 = col_obj1->getUserPointer();

      fcppt::cast::from_void_ptr<object *>(user_pointer0)
          ->exit_internal(*fcppt::cast::from_void_ptr<body::object const *>(user_pointer1));
    }
    ghost0->removeOverlappingObjectInternal(proxy1, dispatcher, proxy0);
  }

  if (ghost1 != nullptr)
  {
    if (ghost0 == nullptr)
    {
      if(ghost1->getUserPointer() == nullptr)
      {
        throw sge::projectile::exception{FCPPT_TEXT("ghost1 has no user pointer!")};
      }
      void *user_pointer1 = ghost1->getUserPointer();
      if(col_obj0 == nullptr)
      {
        throw sge::projectile::exception{FCPPT_TEXT("Collision object0 is null!")};
      }
      if(col_obj0->getUserPointer() == nullptr)
      {
        throw sge::projectile::exception{FCPPT_TEXT("Collision object0 has no user pointer!")};
      }
      void *user_pointer0 = col_obj0->getUserPointer();

      fcppt::cast::from_void_ptr<object *>(user_pointer1)
          ->exit_internal(*fcppt::cast::from_void_ptr<body::object const *>(user_pointer0));
    }
    ghost1->removeOverlappingObjectInternal(proxy0, dispatcher, proxy1);
  }

  return nullptr;
}

[[noreturn]]
void sge::projectile::ghost::detail::pair_callback::removeOverlappingPairsContainingProxy(
    btBroadphaseProxy *, btDispatcher *)
{
  throw sge::projectile::exception{FCPPT_TEXT("removeOverlappingPairs called!")};
}
