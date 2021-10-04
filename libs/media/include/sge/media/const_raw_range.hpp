//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MEDIA_CONST_RAW_RANGE_HPP_INCLUDED
#define SGE_MEDIA_CONST_RAW_RANGE_HPP_INCLUDED

#include <sge/media/const_raw_pointer.hpp>
#include <fcppt/iterator/range_impl.hpp>


namespace sge::media
{

using
const_raw_range
=
fcppt::iterator::range<
	sge::media::const_raw_pointer
>;

}

#endif
