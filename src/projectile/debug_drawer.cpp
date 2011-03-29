#include "declare_local_logger.hpp"
#include <sge/projectile/debug_drawer.hpp>
#include <sge/projectile/world.hpp>
#include <sge/projectile/structure_cast.hpp>
#include <sge/line_drawer/line.hpp>
#include <sge/line_drawer/scoped_lock.hpp>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <sge/renderer/scoped_transform.hpp>
#include <sge/image/color/rgb8.hpp>
#include <sge/image/color/init.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/assert.hpp>
#include <iostream>
#include <ostream>

SGE_PROJECTILE_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("debug_drawer"))

sge::projectile::debug_drawer::debug_drawer(
	world &_world,
	sge::renderer::device_ptr const _renderer)
:
	world_(
		_world.world_),
	renderer_(
		_renderer),
	debug_mode_(
		btIDebugDraw::DBG_NoDebug), // should be zero
	line_drawer_(
		renderer_),
	scoped_lock_()
{
	FCPPT_ASSERT(
		!world_.getDebugDrawer());
	world_.setDebugDrawer(
		this);
}

void
sge::projectile::debug_drawer::update()
{
	scoped_lock_.reset(
		new sge::line_drawer::scoped_lock(
			line_drawer_));

	/*
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("acquired lock"));
	*/

	scoped_lock_->value().clear();

	if (debug_mode_ != btIDebugDraw::DBG_NoDebug)
		world_.debugDrawWorld();

	scoped_lock_.reset();

	/*
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("released lock"));
	*/
}

void
sge::projectile::debug_drawer::render(
	sge::renderer::matrix4 const &mvp)
{
	if (debug_mode_ == btIDebugDraw::DBG_NoDebug)
		return;

	sge::renderer::scoped_transform projection_scope(
		renderer_,
		sge::renderer::matrix_mode::projection,
		mvp);

	sge::renderer::scoped_transform world_scope(
		renderer_,
		sge::renderer::matrix_mode::world,
		sge::renderer::matrix4::identity());
	
	line_drawer_.render();
}

void
sge::projectile::debug_drawer::active(
	bool const _active)
{
	setDebugMode(
		_active
		?
			btIDebugDraw::DBG_DrawWireframe/* | btIDebugDraw::DBG_DrawAabb*/
		:
			btIDebugDraw::DBG_NoDebug);
}

bool 
sge::projectile::debug_drawer::active() const
{
	return debug_mode_ != btIDebugDraw::DBG_NoDebug;
}

sge::projectile::debug_drawer::~debug_drawer()
{
	world_.setDebugDrawer(
		0);
}

// @override
void
sge::projectile::debug_drawer::drawLine(
	btVector3 const &from,
	btVector3 const &to,
	btVector3 const &color)
{
	drawLine(
		from,
		to,
		color,
		color);
}

// @override
void
sge::projectile::debug_drawer::drawLine(
	btVector3 const &from,
	btVector3 const &to,
	btVector3 const &from_color,
	btVector3 const &to_color)
{
	// This MIGHT happen, for example when you use the BvhMeshShape. A
	// better solution than return; here would be to queue up those
	// triangles. TODO
	if(!scoped_lock_)
		return;
	scoped_lock_->value().push_back(
		sge::line_drawer::line(
			structure_cast<sge::renderer::vector3>(
				from),
			structure_cast<sge::renderer::vector3>(
				to),
			sge::image::color::rgb8(
				(sge::image::color::init::red %= from_color.getX())
				(sge::image::color::init::green %= from_color.getY())
				(sge::image::color::init::blue %= from_color.getZ())),
			sge::image::color::rgb8(
				(sge::image::color::init::red %= to_color.getX())
				(sge::image::color::init::green %= to_color.getY())
				(sge::image::color::init::blue %= to_color.getZ()))));
}

// @override
void
sge::projectile::debug_drawer::drawContactPoint(
	btVector3 const &point,
	btVector3 const &normal,
	btScalar distance,
	int /*lifeTime*/,
	btVector3 const &color)
{
	drawLine(
		point,
		point + normal * distance,
		color);
}

// @override
void	
sge::projectile::debug_drawer::draw3dText(
	btVector3 const&,
	char const*)
{
}

// @override
void
sge::projectile::debug_drawer::reportErrorWarning(
	char const* warningString)
{
	std::cerr 
		<< "Debug drawer warning: "
		<< warningString
		<< "\n";
}

// @override
void 
sge::projectile::debug_drawer::setDebugMode(
	int const _debug_mode)
{
	debug_mode_ = _debug_mode;
}

// @override
int 
sge::projectile::debug_drawer::getDebugMode() const
{
	return debug_mode_;
}
