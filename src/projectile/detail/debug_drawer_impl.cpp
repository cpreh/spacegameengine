/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/image/color/rgb8.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <sge/line_drawer/line.hpp>
#include <sge/line_drawer/scoped_lock.hpp>
#include <sge/projectile/world.hpp>
#include <sge/renderer/vector3.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/src/projectile/declare_local_logger.hpp>
#include <sge/src/projectile/structure_cast.hpp>
#include <sge/src/projectile/detail/debug_drawer_impl.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <fcppt/config/external_end.hpp>


SGE_PROJECTILE_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("debug_drawer_impl"))

sge::projectile::detail::debug_drawer_impl::debug_drawer_impl(
	sge::projectile::world &_world,
	sge::renderer::device::core &_renderer)
:
	world_(
		*_world.world_),
	debug_mode_(
		btIDebugDraw::DBG_NoDebug), // should be zero
	line_drawer_(
		_renderer),
	scoped_lock_()
{
	FCPPT_ASSERT_PRE(
		!world_.getDebugDrawer());
	world_.setDebugDrawer(
		this);
}

void
sge::projectile::detail::debug_drawer_impl::update()
{
	scoped_lock_ =
		fcppt::make_unique_ptr<sge::line_drawer::scoped_lock>(
			line_drawer_);

	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("acquired lock"));

	scoped_lock_->value().clear();

	if (debug_mode_ != btIDebugDraw::DBG_NoDebug)
		world_.debugDrawWorld();

	scoped_lock_.reset();

	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("released lock"));
}

void
sge::projectile::detail::debug_drawer_impl::render(
	sge::renderer::context::core &_render_context)
{
	if (debug_mode_ == btIDebugDraw::DBG_NoDebug)
		return;

	line_drawer_.render(
		_render_context);
}

void
sge::projectile::detail::debug_drawer_impl::active(
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
sge::projectile::detail::debug_drawer_impl::active() const
{
	return debug_mode_ != btIDebugDraw::DBG_NoDebug;
}

sge::projectile::detail::debug_drawer_impl::~debug_drawer_impl()
{
	world_.setDebugDrawer(
		0);
}

// @override
void
sge::projectile::detail::debug_drawer_impl::drawLine(
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
sge::projectile::detail::debug_drawer_impl::drawLine(
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
			sge::image::color::any::object(
				sge::image::color::rgb8(
					(sge::image::color::init::red() %= from_color.getX())
					(sge::image::color::init::green() %= from_color.getY())
					(sge::image::color::init::blue() %= from_color.getZ()))),
			sge::image::color::any::object(
				sge::image::color::rgb8(
					(sge::image::color::init::red() %= to_color.getX())
					(sge::image::color::init::green() %= to_color.getY())
					(sge::image::color::init::blue() %= to_color.getZ())))));
}

// @override
void
sge::projectile::detail::debug_drawer_impl::drawContactPoint(
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
sge::projectile::detail::debug_drawer_impl::draw3dText(
	btVector3 const&,
	char const*)
{
}

// @override
void
sge::projectile::detail::debug_drawer_impl::reportErrorWarning(
	char const* warningString)
{
	FCPPT_LOG_WARNING(
		local_log,
		fcppt::log::_
			<<
			fcppt::from_std_string(
				warningString
			)
	);
}

// @override
void
sge::projectile::detail::debug_drawer_impl::setDebugMode(
	int const _debug_mode)
{
	debug_mode_ = _debug_mode;
}

// @override
int
sge::projectile::detail::debug_drawer_impl::getDebugMode() const
{
	return debug_mode_;
}
