#ifndef SGE_COLLISION_TEST_CALLBACK_COMBINER_HPP_INCLUDED
#define SGE_COLLISION_TEST_CALLBACK_COMBINER_HPP_INCLUDED

#include <sge/function/object_fwd.hpp>

namespace sge
{
namespace collision
{

typedef sge::function::object<
	bool (
		bool,
		bool
	)
> test_callback_combiner;

}
}

#endif
