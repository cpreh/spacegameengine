//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_VORBIS_STREAM_UNIQUE_PTR_HPP_INCLUDED
#define SGE_VORBIS_STREAM_UNIQUE_PTR_HPP_INCLUDED

#include <sge/vorbis/stream_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge::vorbis
{

using
stream_unique_ptr
=
fcppt::unique_ptr<
	sge::vorbis::stream
>;

}

#endif
