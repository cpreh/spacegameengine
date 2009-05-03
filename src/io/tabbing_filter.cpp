#include <sge/io/tabbing_filter.hpp>

tabbing_filter::tabbing_filter(
  unsigned &tabs)
:
	first_char(true),
	tabs(tabs)
{
}
