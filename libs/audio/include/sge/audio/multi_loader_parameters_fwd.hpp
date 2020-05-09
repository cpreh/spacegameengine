//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_AUDIO_MULTI_LOADER_PARAMETERS_FWD_HPP_INCLUDED
#define SGE_AUDIO_MULTI_LOADER_PARAMETERS_FWD_HPP_INCLUDED

#include <sge/audio/loader_fwd.hpp>
#include <sge/media/muxer_parameters_fwd.hpp>


namespace sge
{
namespace audio
{

using
multi_loader_parameters
=
sge::media::muxer_parameters<
	sge::audio::loader
>;

}
}

#endif
