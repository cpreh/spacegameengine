#include <sge/container/map_impl.hpp>
#include <sge/string.hpp>
#include <sge/text.hpp>
#include <sge/cout.hpp>
#include <boost/foreach.hpp>
#include <map>

int main()
{
	typedef sge::container::map<
		std::map,
		int,
		sge::string
	> map_type;

	map_type m;

	m.insert(
		42,
		SGE_TEXT("peter")
	);

	BOOST_FOREACH(
		map_type::const_reference r,
		m
	)
		sge::cout
			<< r.first
			<< SGE_TEXT(": ")
			<< r.second;
}
