//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/dim1.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/index/buffer.hpp>
#include <sge/renderer/index/buffer_base.hpp>

sge::renderer::index::buffer::buffer() : sge::renderer::index::buffer_base() {}

sge::renderer::index::buffer::~buffer() = default;

sge::renderer::size_type sge::renderer::index::buffer::linear_size() const
{
  return this->size().w();
}
