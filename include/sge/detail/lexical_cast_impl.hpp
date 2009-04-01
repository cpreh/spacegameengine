#include <sge/sstream.hpp>
#include <sge/bad_lexical_cast.hpp>
#include <sge/type_info.hpp>

template<typename Dest,typename Src>
typename boost::disable_if<boost::is_same<Src,Dest>,Dest>::type const sge::lexical_cast(
	Src const &s)
{
	sge::stringstream ss;
	Dest result;

	if (!(ss << s && ss >> result))
		throw bad_lexical_cast(typeid(Src),typeid(Dest));
	
	return result;
}

template<typename Src>
Src const sge::lexical_cast(
	Src const &s)
{
	return s;
}
