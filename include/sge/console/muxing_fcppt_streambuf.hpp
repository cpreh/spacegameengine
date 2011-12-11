#ifndef SGE_CONSOLE_MUXING_FCPPT_STREAMBUF_HPP_INCLUDED
#define SGE_CONSOLE_MUXING_FCPPT_STREAMBUF_HPP_INCLUDED

#include <sge/console/muxing_streambuf_decl.hpp>
#include <fcppt/char_type.hpp>

namespace sge
{
namespace console
{
typedef
sge::console::muxing_streambuf<fcppt::char_type>
muxing_fcppt_streambuf;
}
}

#endif
