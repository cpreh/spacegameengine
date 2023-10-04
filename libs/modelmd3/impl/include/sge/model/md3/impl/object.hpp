//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_MODEL_MD3_IMPL_OBJECT_HPP_INCLUDED
#define SGE_MODEL_MD3_IMPL_OBJECT_HPP_INCLUDED

#include <sge/model/md3/index_sequence.hpp>
#include <sge/model/md3/load_flags_field_fwd.hpp>
#include <sge/model/md3/object.hpp>
#include <sge/model/md3/optional_normal_sequence_fwd.hpp>
#include <sge/model/md3/optional_texcoord_sequence_fwd.hpp>
#include <sge/model/md3/part_name_sequence.hpp>
#include <sge/model/md3/string.hpp>
#include <sge/model/md3/vertex_sequence.hpp>
#include <sge/model/md3/impl/frame_vector.hpp>
#include <sge/model/md3/impl/surface_vector.hpp>
#include <sge/model/md3/impl/tag_vector.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace sge::model::md3::impl
{

class object : public sge::model::md3::object
{
  FCPPT_NONMOVABLE(object);

public:
  object(
      fcppt::log::object &, // NOLINT(google-runtime-references)
      std::istream &,
      sge::model::md3::load_flags_field);

  ~object() override;

private:
  [[nodiscard]] sge::model::md3::index_sequence
  indices(sge::model::md3::string const &) const override;

  [[nodiscard]] sge::model::md3::vertex_sequence
  vertices(sge::model::md3::string const &) const override;

  [[nodiscard]] sge::model::md3::optional_texcoord_sequence
  texcoords(sge::model::md3::string const &) const override;

  [[nodiscard]] sge::model::md3::optional_normal_sequence
  normals(sge::model::md3::string const &) const override;

  [[nodiscard]] sge::model::md3::part_name_sequence part_names() const override;

  std::size_t vertices_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)

  std::size_t indices_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)

  sge::model::md3::string name_;

  sge::model::md3::impl::frame_vector frames_;

  sge::model::md3::impl::tag_vector tags_;

  sge::model::md3::impl::surface_vector surfaces_;

  [[nodiscard]] sge::model::md3::impl::surface_vector::const_reference
  surface_by_name(sge::model::md3::string const &) const;
};

}

#endif
