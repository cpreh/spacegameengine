//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE2D_MULTI_SYSTEM_PARAMETERS_FWD_HPP_INCLUDED
#define SGE_IMAGE2D_MULTI_SYSTEM_PARAMETERS_FWD_HPP_INCLUDED

#include <sge/image2d/system_fwd.hpp>
#include <sge/media/muxer_parameters_fwd.hpp>


namespace sge
{
namespace image2d
{

typedef
sge::media::muxer_parameters<
	sge::image2d::system
>
multi_system_parameters;

}
}

#endif
