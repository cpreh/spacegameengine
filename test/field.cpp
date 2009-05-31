#include <sge/container/field.hpp>
#include <sge/cout.hpp>
#include <sge/cerr.hpp>
#include <sge/text.hpp>
#include <sge/exception.hpp>
#include <exception>
#include <iostream>
#include <ostream>

int main()
try
{
	typedef sge::container::field<int> field_type;
	field_type f(
		field_type::dim_type(
			2,2));
	f.pos(field_type::vector_type(0,0)) = 0;
	f.pos(field_type::vector_type(1,0)) = 1;
	f.pos(field_type::vector_type(0,1)) = 2;
	f.pos(field_type::vector_type(1,1)) = 3;
	sge::cout << f << SGE_TEXT("\n");
	f.resize_canvas(
		field_type::dim_type(
			1,1),
		9);
	sge::cout << f << SGE_TEXT("\n");
}
catch (sge::exception const &e)
{
	sge::cerr << SGE_TEXT("caught sge exception: ") << e.what() << SGE_TEXT("\n");
}
catch (std::exception const &e)
{
	std::cerr << "caught std exception: " << e.what() << "\n";
}
catch (...)
{
	std::cerr << "caught unknown exception\n";
}
