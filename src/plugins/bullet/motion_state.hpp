#ifndef SGE_BULLET_MOTION_STATE_HPP_INCLUDED
#define SGE_BULLET_MOTION_STATE_HPP_INCLUDED

#include "types.hpp"
#include <bullet/LinearMath/btMotionState.h>
#include <boost/function.hpp>

namespace sge
{
namespace bullet
{
typedef boost::function<void (point const &)> change_callback;

class motion_state : public btMotionState
{
public:
	explicit motion_state(change_callback const &);
	point const pos() const;
	void pos(point const &);
	void getWorldTransform(btTransform &) const;
	void setWorldTransform(btTransform const &);
private:
	btTransform pos_;
	change_callback callback;
};
}
}

#endif
