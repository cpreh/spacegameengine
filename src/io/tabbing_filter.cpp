#include <sge/io/tabbing_filter.hpp>

sge::io::tabbing_filter::tabbing_filter(
  unsigned &tabs)
:
	tabs(tabs),
	first_char(true)
{
}
