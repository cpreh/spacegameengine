//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_MODEL_OBJ_FACE_VERTEX_HPP_INCLUDED
#define SGE_MODEL_OBJ_FACE_VERTEX_HPP_INCLUDED

#include <sge/model/obj/face_vertex_fwd.hpp>
#include <sge/model/obj/normal_index.hpp>
#include <sge/model/obj/texture_coordinate_index.hpp>
#include <sge/model/obj/vertex_coordinate_index.hpp>
#include <sge/model/obj/detail/symbol.hpp>
#include <fcppt/array/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>

namespace sge::model::obj
{

class face_vertex
{
public:
  SGE_MODEL_OBJ_DETAIL_SYMBOL
  face_vertex(
      sge::model::obj::vertex_coordinate_index const &,
      sge::model::obj::texture_coordinate_index const &,
      sge::model::obj::normal_index const &);

  [[nodiscard]] SGE_MODEL_OBJ_DETAIL_SYMBOL sge::model::obj::vertex_coordinate_index
  vertex_coordinate_index() const;

  [[nodiscard]] SGE_MODEL_OBJ_DETAIL_SYMBOL sge::model::obj::texture_coordinate_index
  texture_coordinate_index() const;

  [[nodiscard]] SGE_MODEL_OBJ_DETAIL_SYMBOL sge::model::obj::normal_index normal_index() const;

  [[nodiscard]] SGE_MODEL_OBJ_DETAIL_SYMBOL bool operator==(face_vertex const &) const;

  [[nodiscard]] SGE_MODEL_OBJ_DETAIL_SYMBOL bool operator<(face_vertex const &) const;

private:
  using index_array = fcppt::array::object<std::size_t, 3>;

  index_array indices_;
};

}

#endif
