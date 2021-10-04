//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_IMPL_DETAIL_DEBUG_DRAWER_IMPL_HPP_INCLUDED
#define SGE_PROJECTILE_IMPL_DETAIL_DEBUG_DRAWER_IMPL_HPP_INCLUDED

#include <sge/line_drawer/object.hpp>
#include <sge/line_drawer/scoped_lock.hpp>
#include <sge/projectile/world_ref.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/context_reference_fwd.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <BulletCollision/CollisionDispatch/btCollisionWorld.h>
#include <LinearMath/btIDebugDraw.h>
#include <LinearMath/btVector3.h>
#include <fcppt/config/external_end.hpp>


namespace sge::projectile::detail
{

class debug_drawer_impl
:
	public btIDebugDraw
{
	FCPPT_NONMOVABLE(
		debug_drawer_impl
	);
public:
	debug_drawer_impl(
		fcppt::log::context_reference,
		sge::projectile::world_ref,
		sge::renderer::device::core_ref
	);

	void
	update();

	void
	render(
		sge::renderer::context::core & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)

	void
	active(
		bool
	);

	[[nodiscard]]
	bool
	active() const;

	~debug_drawer_impl()
	override;
private:
	fcppt::log::object log_;

	btCollisionWorld &world_;

	int debug_mode_;

	sge::line_drawer::object line_drawer_;

	using
	scoped_lock_unique_ptr
	=
	fcppt::unique_ptr<
		sge::line_drawer::scoped_lock
	>;

	using
	optional_scoped_lock_unique_ptr
	=
	fcppt::optional::object<
		scoped_lock_unique_ptr
	>;

	optional_scoped_lock_unique_ptr scoped_lock_;

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

	[[nodiscard]]
	int
	getDebugMode() const
	override;
};

}

#endif
