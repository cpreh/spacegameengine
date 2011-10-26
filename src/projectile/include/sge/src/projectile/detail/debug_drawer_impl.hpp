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


#ifndef SGE_SRC_PROJECTILE_DETAIL_DEBUG_DRAWER_IMPL_HPP_INCLUDED
#define SGE_SRC_PROJECTILE_DETAIL_DEBUG_DRAWER_IMPL_HPP_INCLUDED

#include <sge/line_drawer/object.hpp>
#include <sge/line_drawer/scoped_lock.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/matrix4.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <LinearMath/btIDebugDraw.h>
#include <LinearMath/btVector3.h>
#include <BulletCollision/CollisionDispatch/btCollisionWorld.h>
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
	explicit
	debug_drawer_impl(
		world &,
		sge::renderer::device &);

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
	sge::renderer::device &renderer_;
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
