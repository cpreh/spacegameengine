#ifndef SGE_BULLET_CONSTRAINT_HPP_INCLUDED
#define SGE_BULLET_CONSTRAINT_HPP_INCLUDED

#include "types.hpp"
#include <bullet/BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace bullet
{
class constraint 
{
	SGE_NONCOPYABLE(constraint)
	public:
	constraint(
		world_type &,
		body_type &body,
		body_type &zero_body);
		
	~constraint();
	private:
	world_type &world;
	btGeneric6DofConstraint constraint_;
};
}
}

#endif
