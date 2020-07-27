//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_IMPL_BODY_DETAIL_MOTION_STATE_HPP_INCLUDED
#define SGE_PROJECTILE_IMPL_BODY_DETAIL_MOTION_STATE_HPP_INCLUDED

#include <sge/projectile/body/object_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <LinearMath/btMotionState.h>
#include <LinearMath/btTransform.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace projectile
{
namespace body
{
namespace detail
{

// This is just a trampoline class because I couldn't derive
// body::object itself from btMotionState (since then I would break
// the pimpl stuff).
class motion_state
:
	public btMotionState
{
	FCPPT_NONMOVABLE(
		motion_state
	);
public:
	explicit
	motion_state(
		sge::projectile::body::object_ref
	);

	~motion_state()
	override;
private:
	sge::projectile::body::object_ref const body_;

	void
	getWorldTransform(
		btTransform &
	) const
	override;

	void
	setWorldTransform(
		btTransform const &
	)
	override;
};

}
}
}
}

#endif
