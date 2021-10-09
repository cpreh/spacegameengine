//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/texture/mipmap/level_count.hpp>
#include <sge/d3d9/texture/mipmap/level_count_visitor.hpp>
#include <sge/renderer/texture/mipmap/object.hpp>
#include <fcppt/variant/apply.hpp>
#include <fcppt/variant/object_impl.hpp>

UINT sge::d3d9::texture::mipmap::level_count(sge::renderer::texture::mipmap::object const &_object)
{
  return fcppt::variant::apply(mipmap::level_count_visitor(), _object.variant());
}
