#include <sge/collision/parameters.hpp>

sge::collision::parameters::parameters(test_callback const &_test)
	: test_(_test)
{}

sge::collision::test_callback const sge::collision::parameters::test() const
{
	return test_;
}
