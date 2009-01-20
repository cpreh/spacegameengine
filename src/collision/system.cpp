#include <sge/collision/system.hpp>

sge::collision::system::system(test_callback const &_test)
	: test_(_test)
{
}

bool sge::collision::system::test(sattelite const &a,sattelite const &b)
{
	return test_(a,b);
}

sge::collision::system::~system() {}
