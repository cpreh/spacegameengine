/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "debug_drawer_impl.hpp"
#include "../declare_local_logger.hpp"
#include "../structure_cast.hpp"
#include <sge/projectile/world.hpp>
#include <sge/line_drawer/line.hpp>
#include <sge/line_drawer/scoped_lock.hpp>
#include <sge/renderer/scoped_transform.hpp>
#include <sge/image/color/rgb8.hpp>
#include <sge/image/color/init.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <iostream>
#include <ostream>

SGE_PROJECTILE_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("debug_drawer_impl"))

sge::projectile::detail::debug_drawer_impl::debug_drawer_impl(
	world &_world,
	sge::renderer::device &_renderer)
:
	world_(
		*_world.world_),
	renderer_(
		_renderer),
	debug_mode_(
		btIDebugDraw::DBG_NoDebug), // should be zero
	line_drawer_(
		renderer_),
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
	scoped_lock_.take(
		fcppt::make_unique_ptr<sge::line_drawer::scoped_lock>(
			fcppt::ref(
				line_drawer_)));

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
sge::projectile::detail::debug_drawer_impl::render(
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
					(sge::image::color::init::red %= from_color.getX())
					(sge::image::color::init::green %= from_color.getY())
					(sge::image::color::init::blue %= from_color.getZ()))),
			sge::image::color::any::object(
				sge::image::color::rgb8(
					(sge::image::color::init::red %= to_color.getX())
					(sge::image::color::init::green %= to_color.getY())
					(sge::image::color::init::blue %= to_color.getZ())))));
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
	// FIXME!
	std::cerr
		<< "Debug drawer warning: "
		<< warningString
		<< "\n";
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
