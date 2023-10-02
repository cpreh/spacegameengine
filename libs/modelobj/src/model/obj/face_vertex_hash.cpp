//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/model/obj/face_vertex.hpp>
#include <sge/model/obj/face_vertex_hash.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/hash_combine.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <functional>
#include <fcppt/config/external_end.hpp>

std::size_t std::hash<sge::model::obj::face_vertex>::operator()(
    sge::model::obj::face_vertex const &_vertex) const noexcept
{
  return fcppt::hash_combine(
      _vertex.vertex_coordinate_index().get(),
      fcppt::hash_combine(_vertex.texture_coordinate_index().get(), _vertex.normal_index().get()));
}
