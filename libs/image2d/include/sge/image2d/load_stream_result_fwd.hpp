//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE2D_LOAD_STREAM_RESULT_FWD_HPP_INCLUDED
#define SGE_IMAGE2D_LOAD_STREAM_RESULT_FWD_HPP_INCLUDED

#include <sge/image2d/file_fwd.hpp>
#include <sge/media/load_stream_result_fwd.hpp>


namespace sge
{
namespace image2d
{

typedef
sge::media::load_stream_result<
	sge::image2d::file
>
load_stream_result;

}
}

#endif
