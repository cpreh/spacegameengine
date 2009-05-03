#include <boost/iostreams/operations.hpp>

template<typename Sink>
bool sge::io::tabbing_filter::put(
  Sink &s,
  int c)
{
  if (first_char)
  {
    if (!put_tabs(s))
      return false;
    first_char = false;
    return boost::iostreams::put(
      s,
      c);
  }

  if (c != '\n')
    return boost::iostreams::put(s,c);

  if (!boost::iostreams::put(s,c))
    return false;

  return put_tabs(s);
}


template<typename Sink>
bool sge::io::tabbing_filter::put_tabs(
  Sink &dest)
{
  for (unsigned i = 0; i < tabs; ++i)
    if (!boost::iostreams::put(dest,'\t'))
      return false;
  return true;
}
