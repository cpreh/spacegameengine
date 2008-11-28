#ifndef SGE_GUI_UTILITY_PTR_DELETE_FIRST_HPP_INCLUDED
#define SGE_GUI_UTILITY_PTR_DELETE_FIRST_HPP_INCLUDED

namespace sge
{
namespace gui
{
namespace utility
{
template<typename Container,typename Ptr>
void ptr_delete_first(Container &c,Ptr const s)
{
  for (typename Container::iterator b = c.begin();b != c.end(); ++b)
  {
    if (&(*b) != s)
      continue;
    c.erase(b);
    break;
  }
}
}
}
}

#endif
