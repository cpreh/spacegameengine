#ifndef SGE_GUI_UTILITY_UNLIMITED_TEXT_SIZE_HPP_INCLUDED
#define SGE_GUI_UTILITY_UNLIMITED_TEXT_SIZE_HPP_INCLUDED
 
#include <sge/font/metrics_fwd.hpp>
#include <sge/gui/dim.hpp>
#include <sge/string.hpp>
 
namespace sge
{
namespace gui
{
namespace utility
{
dim const unlimited_text_size(
	font::metrics_ptr,
	string const &);
}
}
}

#endif
