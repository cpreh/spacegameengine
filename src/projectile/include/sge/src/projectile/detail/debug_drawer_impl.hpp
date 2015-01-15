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


#ifndef SGE_SRC_PROJECTILE_DETAIL_DEBUG_DRAWER_IMPL_HPP_INCLUDED
#define SGE_SRC_PROJECTILE_DETAIL_DEBUG_DRAWER_IMPL_HPP_INCLUDED

#include <sge/line_drawer/object.hpp>
#include <sge/line_drawer/scoped_lock.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <BulletCollision/CollisionDispatch/btCollisionWorld.h>
#include <LinearMath/btIDebugDraw.h>
#include <LinearMath/btVector3.h>
#include <memory>
#include <fcppt/config/external_end.hpp>


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
	debug_drawer_impl(
		sge::projectile::world &,
		sge::renderer::device::core &);

	void
	update();

	void
	render(
		sge::renderer::context::core &);

	void
	active(
		bool);

	bool
	active() const;

	~debug_drawer_impl()
	override;
private:
	btCollisionWorld &world_;
	int debug_mode_;
	sge::line_drawer::object line_drawer_;
	std::unique_ptr<sge::line_drawer::scoped_lock> scoped_lock_;

	void
	drawLine(
		btVector3 const &from,
		btVector3 const &to,
		btVector3 const &color
	)
	override;

	void
	drawLine(
		btVector3 const &from,
		btVector3 const &to,
		btVector3 const &from_color,
		btVector3 const &to_color
	)
	override;

	void
	drawContactPoint(
		btVector3 const &PointOnB,
		btVector3 const &normalOnB,
		btScalar distance,
		int lifeTime,
		btVector3 const & color
	)
	override;

	void
	draw3dText(
		btVector3 const&location,
		char const*textString
	)
	override;

	void
	reportErrorWarning(
		char const* warningString
	)
	override;

	void
	setDebugMode(
		int
	)
	override;

	int
	getDebugMode() const
	override;
};
}
}
}

#endif
