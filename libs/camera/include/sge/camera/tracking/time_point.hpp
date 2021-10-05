//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_TRACKING_TIME_POINT_HPP_INCLUDED
#define SGE_CAMERA_TRACKING_TIME_POINT_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge
{
namespace camera
{
namespace tracking
{

FCPPT_DECLARE_STRONG_TYPEDEF(
	sge::renderer::scalar,
	time_point
);

}
}
}

#endif
