//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MEDIA_CONST_RAW_RANGE_HPP_INCLUDED
#define SGE_MEDIA_CONST_RAW_RANGE_HPP_INCLUDED

#include <sge/media/const_raw_pointer.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace media
{

typedef boost::iterator_range<
	sge::media::const_raw_pointer
> const_raw_range;

}
}

#endif
