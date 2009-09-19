#ifndef SGE_COLLISION_TEST_CALLBACK_HPP_INCLUDED
#define SGE_COLLISION_TEST_CALLBACK_HPP_INCLUDED

#include <sge/collision/test_callback_fn.hpp>
#include <boost/function.hpp>

namespace sge
{
namespace collision
{
typedef boost::function<test_callback_fn> test_callback;
}
}

#endif
