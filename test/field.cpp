#include <sge/container/field.hpp>
#include <sge/cout.hpp>
#include <sge/text.hpp>

int main()
{
	sge::container::field<int> f;
	f.pos(0,0) = 0;
	f.pos(1,0) = 1;
	f.pos(0,1) = 2;
	f.pos(1,1) = 3;
	sge::cout << f << SGE_TEXT("\n");
}
