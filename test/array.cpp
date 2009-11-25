#include <sge/assign/make_array.hpp>
#include <sge/cout.hpp>
#include <sge/text.hpp>
#include <boost/foreach.hpp>

int main()
{
	std::tr1::array<int,3> const a =
		sge::assign::make_array<int>(3)(4)(5);

	BOOST_FOREACH(int x,a)
	{
		sge::cout << x << SGE_TEXT("\n");
	}
}
