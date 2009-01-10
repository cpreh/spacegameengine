#ifndef SGE_GUI_UTILITY_PTR_FIND_HPP_INCLUDED
#define SGE_GUI_UTILITY_PTR_FIND_HPP_INCLUDED

#include <sge/container/ptr_equal.hpp>
#include <algorithm>

namespace sge
{
namespace gui
{
namespace utility
{
template<typename Beg,typename End,typename Ptr>
Beg ptr_find(Beg b,End const e,Ptr const s)
{
	return std::find_if(
 		b,
		e,
		container::make_ptr_equal(
			s));
/*
  for (;b != e; ++b)
    if (&(*b) == s)
      return b;
  return b;*/
}
}
}
}

#endif
