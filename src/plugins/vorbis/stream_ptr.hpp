#ifndef SGE_VORBIS_STREAM_PTR_HPP_INCLUDED
#define SGE_VORBIS_STREAM_PTR_HPP_INCLUDED

#include <fcppt/unique_ptr.hpp>
// iosfwd here?
#include <istream>

namespace sge
{
namespace vorbis
{
typedef
fcppt::unique_ptr<std::istream>
stream_ptr;
}
}

#endif
