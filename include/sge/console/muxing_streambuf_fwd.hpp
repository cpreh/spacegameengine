#ifndef SGE_CONSOLE_MUXING_STREAMBUF_FWD_HPP_INCLUDED
#define SGE_CONSOLE_MUXING_STREAMBUF_FWD_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace console
{
template<typename Char,typename Traits = std::char_traits<Char> >
class muxing_streambuf;
}
}

#endif
