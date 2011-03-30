#ifndef SGE_PROJECTILE_BODY_DETAIL_MOTION_STATE_HPP_INCLUDED
#define SGE_PROJECTILE_BODY_DETAIL_MOTION_STATE_HPP_INCLUDED

#include <sge/projectile/body/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <LinearMath/btTransform.h>
#include <LinearMath/btMotionState.h>

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
FCPPT_NONCOPYABLE(
	motion_state);
public:
	explicit
	motion_state(
		object &);

	~motion_state();
private:
	object &body_;

	// @override
	void	
	getWorldTransform(
		btTransform &) const;

	// @override
	void	
	setWorldTransform(
		btTransform const &);
};
}
}
}
}

#endif
