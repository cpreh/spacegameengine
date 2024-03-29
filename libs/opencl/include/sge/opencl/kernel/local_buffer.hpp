//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENCL_KERNEL_LOCAL_BUFFER_HPP_INCLUDED
#define SGE_OPENCL_KERNEL_LOCAL_BUFFER_HPP_INCLUDED

#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/memory_object/byte_size.hpp>

namespace sge::opencl::kernel
{
class local_buffer
{
public:
  SGE_OPENCL_DETAIL_SYMBOL explicit local_buffer(sge::opencl::memory_object::byte_size const &);

  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL sge::opencl::memory_object::byte_size::value_type byte_size() const;

private:
  sge::opencl::memory_object::byte_size byte_size_;
};
}

#endif
