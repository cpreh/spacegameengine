//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/model/obj/face_vertex.hpp>
#include <sge/model/obj/normal_index.hpp>
#include <sge/model/obj/texture_coordinate_index.hpp>
#include <sge/model/obj/vertex_coordinate_index.hpp>
#include <fcppt/array/comparison.hpp>
#include <fcppt/array/get.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>

sge::model::obj::face_vertex::face_vertex(
    sge::model::obj::vertex_coordinate_index const &_vertex_coordinate_index,
    sge::model::obj::texture_coordinate_index const &_texture_coordinate_index,
    sge::model::obj::normal_index const &_normal_index)
    : indices_{_vertex_coordinate_index.get(), _texture_coordinate_index.get(), _normal_index.get()}
{
}

sge::model::obj::vertex_coordinate_index
sge::model::obj::face_vertex::vertex_coordinate_index() const
{
  return sge::model::obj::vertex_coordinate_index{fcppt::array::get<0>(indices_)};
}

sge::model::obj::texture_coordinate_index
sge::model::obj::face_vertex::texture_coordinate_index() const
{
  return sge::model::obj::texture_coordinate_index{fcppt::array::get<1>(indices_)};
}

sge::model::obj::normal_index sge::model::obj::face_vertex::normal_index() const
{
  return sge::model::obj::normal_index{fcppt::array::get<2>(indices_)};
}

bool sge::model::obj::face_vertex::operator==(face_vertex const &_other) const
{
  return indices_ == _other.indices_;
}

bool sge::model::obj::face_vertex::operator<(face_vertex const &_other) const
{
  return std::ranges::lexicographical_compare(this->indices_, _other.indices_);
}
