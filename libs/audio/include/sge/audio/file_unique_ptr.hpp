//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_AUDIO_FILE_UNIQUE_PTR_HPP_INCLUDED
#define SGE_AUDIO_FILE_UNIQUE_PTR_HPP_INCLUDED

#include <sge/audio/file_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace audio
{

typedef
fcppt::unique_ptr<
	sge::audio::file
>
file_unique_ptr;

}
}

#endif
