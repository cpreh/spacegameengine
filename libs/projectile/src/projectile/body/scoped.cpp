//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/projectile/world.hpp>
#include <sge/projectile/world_ref.hpp>
#include <sge/projectile/body/object_ref.hpp>
#include <sge/projectile/body/scoped.hpp>
#include <sge/projectile/group/sequence.hpp>

sge::projectile::body::scoped::scoped(
    sge::projectile::world_ref const _world,
    sge::projectile::body::object_ref const _object,
    sge::projectile::group::sequence const &_groups)
    : world_(_world), object_(_object)
{
  world_.get().add_body(object_, _groups);
}

sge::projectile::body::scoped::~scoped() { world_.get().remove_body(object_.get()); }
