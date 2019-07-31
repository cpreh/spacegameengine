//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_DIM2_HPP_INCLUDED
#define SGE_OPENCL_DIM2_HPP_INCLUDED

#include <sge/opencl/size_type.hpp>
#include <fcppt/math/dim/static.hpp>

namespace sge
{
namespace opencl
{
typedef
fcppt::math::dim::static_<sge::opencl::size_type,2>
dim2;
}
}

#endif
