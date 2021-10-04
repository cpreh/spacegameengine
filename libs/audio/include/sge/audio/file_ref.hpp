//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_AUDIO_FILE_REF_HPP_INCLUDED
#define SGE_AUDIO_FILE_REF_HPP_INCLUDED

#include <sge/audio/file_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge::audio
{

using
file_ref
=
fcppt::reference<
	sge::audio::file
>;

}

#endif
