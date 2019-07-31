//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_AUDIO_FILE_EXCEPTION_FWD_HPP_INCLUDED
#define SGE_AUDIO_FILE_EXCEPTION_FWD_HPP_INCLUDED

#include <sge/audio/exception_fwd.hpp>
#include <sge/media/file_exception_fwd.hpp>


namespace sge
{
namespace audio
{

typedef
sge::media::file_exception<
	sge::audio::exception
>
file_exception;

}
}

#endif
