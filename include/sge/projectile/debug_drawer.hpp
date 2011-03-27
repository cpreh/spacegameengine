#ifndef SGE_PROJECTILE_DEBUG_DRAWER_HPP_INCLUDED
#define SGE_PROJECTILE_DEBUG_DRAWER_HPP_INCLUDED

#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/symbol.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/line_drawer/object.hpp>
#include <sge/line_drawer/scoped_lock.hpp>
#include <sge/renderer/matrix4.hpp>
#include <bullet/BulletCollision/CollisionDispatch/btCollisionWorld.h>
#include <bullet/LinearMath/btIDebugDraw.h>
#include <bullet/LinearMath/btVector3.h>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sge
{
namespace projectile
{
/// bullet offers registering a debug drawer to draw contact points or
/// just shapes. This class implements this interface, caching all the
/// lines and drawing them at once (if you don't do that, it'll be
/// super-slow).
class debug_drawer
:
	public btIDebugDraw
{
public:	
	SGE_PROJECTILE_SYMBOL explicit
	debug_drawer(
		world &,
		sge::renderer::device_ptr);

	// Updates the line cache
	SGE_PROJECTILE_SYMBOL void
	update();

	// Renders the lines
	SGE_PROJECTILE_SYMBOL void
	render(
		sge::renderer::matrix4 const &);

	SGE_PROJECTILE_SYMBOL void
	active(
		bool);

	SGE_PROJECTILE_SYMBOL bool
	active() const;

	SGE_PROJECTILE_SYMBOL ~debug_drawer();
private:
	// @override
	void
	drawLine(
		btVector3 const &from,
		btVector3 const &to,
		btVector3 const &color);

	// @override
	void
	drawLine(
		btVector3 const &from,
		btVector3 const &to,
		btVector3 const &from_color,
		btVector3 const &to_color);

	// @override
	void
	drawContactPoint(
		btVector3 const &PointOnB,
		btVector3 const &normalOnB,
		btScalar distance,
		int lifeTime,
		btVector3 const & color);

	// @override
	void	
	draw3dText(
		btVector3 const&location,
		char const*textString);
	
	// @override
	void
	reportErrorWarning(
		char const* warningString);

	// @override
	void 
	setDebugMode(
		int);

	// @override
	int 
	getDebugMode() const;

	btCollisionWorld &world_;
	sge::renderer::device_ptr const renderer_;
	int debug_mode_;
	sge::line_drawer::object line_drawer_;
	fcppt::scoped_ptr<sge::line_drawer::scoped_lock> scoped_lock_;
};
}
}

#endif
