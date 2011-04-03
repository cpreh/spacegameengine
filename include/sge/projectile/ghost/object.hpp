#ifndef SGE_PROJECTILE_GHOST_OBJECT_HPP_INCLUDED
#define SGE_PROJECTILE_GHOST_OBJECT_HPP_INCLUDED

#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/body/object_fwd.hpp>
#include <sge/projectile/ghost/body_enter_fn.hpp>
#include <sge/projectile/ghost/body_enter.hpp>
#include <sge/projectile/ghost/body_exit_fn.hpp>
#include <sge/projectile/ghost/body_exit.hpp>
#include <sge/projectile/ghost/detail/pair_callback_fwd.hpp>
#include <sge/projectile/ghost/parameters_fwd.hpp>
#include <sge/projectile/group/object_fwd.hpp>
#include <sge/projectile/symbol.hpp>
#include <sge/projectile/vector2.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object.hpp>

class btCollisionShape;
class btPairCachingGhostObject;

namespace sge
{
namespace projectile
{
namespace ghost
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_PROJECTILE_SYMBOL explicit
	object(
		parameters const &);

	SGE_PROJECTILE_SYMBOL sge::projectile::vector2 const
	position() const;

	SGE_PROJECTILE_SYMBOL void
	position(
		sge::projectile::vector2 const &);

	SGE_PROJECTILE_SYMBOL fcppt::signal::auto_connection
	body_enter(
		sge::projectile::ghost::body_enter const &);

	SGE_PROJECTILE_SYMBOL fcppt::signal::auto_connection
	body_exit(
		sge::projectile::ghost::body_exit const &);

	SGE_PROJECTILE_SYMBOL ~object();
private:
	friend class detail::pair_callback;
	friend class sge::projectile::world;

	fcppt::signal::object<body_enter_fn> body_enter_;
	fcppt::signal::object<body_exit_fn> body_exit_;
	fcppt::scoped_ptr<btCollisionShape> box_shape_;
	fcppt::scoped_ptr<btPairCachingGhostObject> ghost_object_;

	void
	enter_internal(
		body::object const &);

	void
	exit_internal(
		body::object const &);
};
}
}
}

#endif
