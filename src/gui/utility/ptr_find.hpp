#ifndef SGE_GUI_UTILITY_PTR_FIND_HPP_INCLUDED
#define SGE_GUI_UTILITY_PTR_FIND_HPP_INCLUDED

namespace sge
{
namespace gui
{
namespace utility
{
template<typename Beg,typename End,typename Ptr>
Beg ptr_find(Beg b,End const e,Ptr const s)
{
  for (;b != e; ++b)
    if (&(*b) == s)
      return b;
  return b;
}
}
}
}

#endif
