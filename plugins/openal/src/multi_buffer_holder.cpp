//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/openal/multi_buffer_holder.hpp>
#include <sge/openal/funcs/delete_multi_buffers.hpp>
#include <sge/openal/funcs/gen_multi_buffers.hpp>

sge::openal::multi_buffer_holder::multi_buffer_holder(size_type const _size)
    : container_(sge::openal::funcs::gen_multi_buffers(_size))
{
}

sge::openal::multi_buffer_holder::~multi_buffer_holder()
{
  sge::openal::funcs::delete_multi_buffers(container_);
}

sge::openal::buffer_id_container const &sge::openal::multi_buffer_holder::container() const
{
  return container_;
}
