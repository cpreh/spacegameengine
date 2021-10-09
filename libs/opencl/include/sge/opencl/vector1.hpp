//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENCL_VECTOR1_HPP_INCLUDED
#define SGE_OPENCL_VECTOR1_HPP_INCLUDED

#include <sge/opencl/size_type.hpp>
#include <fcppt/math/vector/static.hpp>

namespace sge
{
namespace opencl
{
typedef fcppt::math::vector::static_<sge::opencl::size_type, 1> vector1;
}
}

#endif
