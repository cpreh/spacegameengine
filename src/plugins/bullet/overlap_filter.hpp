#ifndef SGE_BULLET_OVERLAP_FILTER_HPP_INCLUDED
#define SGE_BULLET_OVERLAP_FILTER_HPP_INCLUDED

#include <sge/collision/test_callback_fn.hpp>
#include <sge/collision/test_callback.hpp>
#include <sge/collision/test_callback_combiner.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <BulletCollision/BroadphaseCollision/btOverlappingPairCache.h>

namespace sge
{
namespace bullet
{
class overlap_filter
:
	public btOverlapFilterCallback
{
public:
	bool 
	needBroadphaseCollision(
		btBroadphaseProxy*,
		btBroadphaseProxy*) const;
	
	fcppt::signal::auto_connection
	register_callback(
		collision::test_callback const &);
	
	void
	combiner(
		collision::test_callback_combiner const &);
private:
	fcppt::signal::object
	<
		collision::test_callback_fn
	> test_callback_;
};
}
}

#endif
