#ifndef SGE_PROJECTILE_DETAIL_DEBUG_DRAWER_IMPL_HPP_INCLUDED
#define SGE_PROJECTILE_DETAIL_DEBUG_DRAWER_IMPL_HPP_INCLUDED

#include <sge/projectile/world_fwd.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/line_drawer/object.hpp>
#include <sge/line_drawer/scoped_lock.hpp>
#include <sge/renderer/matrix4.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <LinearMath/btIDebugDraw.h>
#include <LinearMath/btVector3.h>
#include <BulletCollision/CollisionDispatch/btCollisionWorld.h>

namespace sge
{
namespace projectile
{
namespace detail
{
class debug_drawer_impl
:
	public btIDebugDraw
{
FCPPT_NONCOPYABLE(
	debug_drawer_impl);
public:
	explicit
	debug_drawer_impl(
		world &,
		sge::renderer::device_ptr);

	void
	update();

	void
	render(
		sge::renderer::matrix4 const &);

	void
	active(
		bool);

	bool
	active() const;

	~debug_drawer_impl();
private:
	btCollisionWorld &world_;
	sge::renderer::device_ptr const renderer_;
	int debug_mode_;
	sge::line_drawer::object line_drawer_;
	fcppt::scoped_ptr<sge::line_drawer::scoped_lock> scoped_lock_;

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
};
}
}
}

#endif
