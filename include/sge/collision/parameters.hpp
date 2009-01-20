#ifndef SGE_COLLISION_PARAMETERS_HPP_INCLUDED
#define SGE_COLLISION_PARAMETERS_HPP_INCLUDED

#include "callbacks.hpp"
#include "../export.hpp"

namespace sge
{
namespace collision
{
class parameters
{
	public:
	SGE_SYMBOL explicit parameters(test_callback const &);
	SGE_SYMBOL test_callback const test() const;
	private:
	test_callback test_;
};
}
}

#endif
