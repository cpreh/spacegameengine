#ifndef SGE_AUDIO_BUFFER_PTR_HPP_INCLUDED
#define SGE_AUDIO_BUFFER_PTR_HPP_INCLUDED

#include <sge/audio/buffer_fwd.hpp>
#include <fcppt/shared_ptr.hpp>

namespace sge
{
namespace audio
{
typedef
fcppt::shared_ptr<buffer>
buffer_ptr;
}
}

#endif
