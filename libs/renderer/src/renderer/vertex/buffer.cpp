//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/dim1.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/buffer_base.hpp>

sge::renderer::vertex::buffer::buffer() : sge::renderer::vertex::buffer_base() {}

sge::renderer::vertex::buffer::~buffer() = default;

sge::renderer::size_type sge::renderer::vertex::buffer::linear_size() const
{
  return this->size().w();
}
