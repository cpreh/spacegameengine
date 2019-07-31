//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_MEMORY_OBJECT_IMAGE_PLANAR_PITCH_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_IMAGE_PLANAR_PITCH_HPP_INCLUDED

#include <sge/opencl/size_type.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge
{
namespace opencl
{
namespace memory_object
{
namespace image
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sge::opencl::size_type,
	planar_pitch
);

}
}
}
}

#endif
