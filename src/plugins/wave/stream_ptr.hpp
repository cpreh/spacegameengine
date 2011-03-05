#ifndef SGE_WAVE_STREAM_PTR_HPP_INCLUDED
#define SGE_WAVE_STREAM_PTR_HPP_INCLUDED

#include <fcppt/unique_ptr.hpp>
#include <istream>

namespace sge
{
namespace wave
{
typedef
fcppt::unique_ptr<std::istream>
stream_ptr;
}
}

#endif
