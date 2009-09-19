#ifndef SGE_COLLISION_TEST_CALLBACK_COMBINER_HPP_INCLUDED
#define SGE_COLLISION_TEST_CALLBACK_COMBINER_HPP_INCLUDED

#include <boost/function.hpp>

namespace sge
{
namespace collision
{
typedef boost::function<bool (bool,bool)> test_callback_combiner;
}
}

#endif
