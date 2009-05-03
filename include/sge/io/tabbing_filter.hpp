#ifndef SGE_IO_TABBING_FILTER_HPP_INCLUDED
#define SGE_IO_TABBING_FILTER_HPP_INCLUDED

#include <boost/iostreams/concepts.hpp>

namespace sge
{
namespace io
{
class tabbing_filter
  : public boost::iostreams::output_filter
{
public:
  tabbing_filter(unsigned &);

  template<typename Sink>
  bool put(
    Sink &,
    int);
private:
  unsigned &tabs;
  bool first_char;

  template<typename Sink>
  bool put_tabs(Sink &);
};

}
}

#include "detail/tabbing_filter_impl.hpp"

#endif
