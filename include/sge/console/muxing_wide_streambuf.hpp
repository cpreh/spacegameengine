#ifndef SGE_CONSOLE_MUXING_WIDE_STREAMBUF_HPP_INCLUDED
#define SGE_CONSOLE_MUXING_WIDE_STREAMBUF_HPP_INCLUDED

#include <sge/console/muxing_streambuf_decl.hpp>

namespace sge
{
namespace console
{
typedef
sge::console::muxing_streambuf<wchar_t>
muxing_wide_streambuf;
}
}

#endif
