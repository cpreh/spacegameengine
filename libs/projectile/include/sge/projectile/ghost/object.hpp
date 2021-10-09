//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PROJECTILE_GHOST_OBJECT_HPP_INCLUDED
#define SGE_PROJECTILE_GHOST_OBJECT_HPP_INCLUDED

#include <sge/projectile/vector2.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/body/object_fwd.hpp>
#include <sge/projectile/detail/symbol.hpp>
#include <sge/projectile/ghost/body_enter.hpp>
#include <sge/projectile/ghost/body_enter_fn.hpp>
#include <sge/projectile/ghost/body_exit.hpp>
#include <sge/projectile/ghost/body_exit_fn.hpp>
#include <sge/projectile/ghost/parameters_fwd.hpp>
#include <sge/projectile/ghost/detail/pair_callback_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>

class btCollisionShape;
class btPairCachingGhostObject;

namespace sge::projectile::ghost
{
class object
{
  FCPPT_NONMOVABLE(object);

public:
  SGE_PROJECTILE_DETAIL_SYMBOL
  explicit object(sge::projectile::ghost::parameters const &);

  [[nodiscard]] SGE_PROJECTILE_DETAIL_SYMBOL sge::projectile::vector2 position() const;

  SGE_PROJECTILE_DETAIL_SYMBOL
  void position(sge::projectile::vector2 const &);

  [[nodiscard]] SGE_PROJECTILE_DETAIL_SYMBOL fcppt::signal::auto_connection
  body_enter(sge::projectile::ghost::body_enter &&);

  [[nodiscard]] SGE_PROJECTILE_DETAIL_SYMBOL fcppt::signal::auto_connection
  body_exit(sge::projectile::ghost::body_exit &&);

  SGE_PROJECTILE_DETAIL_SYMBOL
  ~object();

private:
  friend class sge::projectile::ghost::detail::pair_callback;
  friend class sge::projectile::world;

  fcppt::log::object &log_;
  fcppt::signal::object<sge::projectile::ghost::body_enter_fn> body_enter_;
  fcppt::signal::object<sge::projectile::ghost::body_exit_fn> body_exit_;
  fcppt::unique_ptr<btCollisionShape> const box_shape_;
  fcppt::unique_ptr<btPairCachingGhostObject> const ghost_object_;

  void enter_internal(sge::projectile::body::object const &);

  void exit_internal(sge::projectile::body::object const &);
};

}

#endif
