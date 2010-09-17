#ifndef MAJUTSU_ROLE_HPP_INCLUDED
#define MAJUTSU_ROLE_HPP_INCLUDED

namespace majutsu
{

template<
	typename T,
	typename Alias = T
>
struct role
:
T
{
	typedef T wrapped;

	typedef Alias alias;
};

}

#endif
