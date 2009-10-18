#ifndef SGE_COLLISION_TEST_CALLBACK_FN_HPP_INCLUDED
#define SGE_COLLISION_TEST_CALLBACK_FN_HPP_INCLUDED

#include <sge/collision/satellite_fwd.hpp>

namespace sge
{
namespace collision
{
typedef 
bool 
test_callback_fn(
	satellite const &,
	satellite const &);
}
}

#endif
