//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SHADER_PAIR_HPP_INCLUDED
#define SGE_SHADER_PAIR_HPP_INCLUDED

#include <sge/cg/program/object.hpp>
#include <sge/renderer/cg/loaded_program_unique_ptr.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/shader/context_fwd.hpp>
#include <sge/shader/context_ref.hpp>
#include <sge/shader/optional_cflags.hpp>
#include <sge/shader/pixel_program_path.hpp>
#include <sge/shader/pixel_program_stream.hpp>
#include <sge/shader/scoped_pair_fwd.hpp>
#include <sge/shader/vertex_program_path.hpp>
#include <sge/shader/vertex_program_stream.hpp>
#include <sge/shader/detail/symbol.hpp>
#include <sge/shader/parameter/planar_texture_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_set>
#include <fcppt/config/external_end.hpp>

namespace sge::shader
{

class pair
{
  FCPPT_NONMOVABLE(pair);

public:
  SGE_SHADER_DETAIL_SYMBOL
  pair(
      sge::shader::context_ref,
      sge::renderer::vertex::declaration const &,
      sge::shader::vertex_program_path const &,
      sge::shader::pixel_program_path const &,
      sge::shader::optional_cflags const &);

  SGE_SHADER_DETAIL_SYMBOL
  pair(
      sge::shader::context_ref,
      sge::renderer::vertex::declaration const &,
      sge::shader::vertex_program_stream const &,
      sge::shader::pixel_program_stream const &,
      sge::shader::optional_cflags const &);

  [[nodiscard]] SGE_SHADER_DETAIL_SYMBOL sge::shader::context &context() const;

  [[nodiscard]] SGE_SHADER_DETAIL_SYMBOL sge::cg::program::object &vertex_program();

  [[nodiscard]] SGE_SHADER_DETAIL_SYMBOL sge::cg::program::object &pixel_program();

  [[nodiscard]] SGE_SHADER_DETAIL_SYMBOL sge::renderer::cg::loaded_program &loaded_vertex_program();

  [[nodiscard]] SGE_SHADER_DETAIL_SYMBOL sge::renderer::cg::loaded_program &loaded_pixel_program();

  SGE_SHADER_DETAIL_SYMBOL
  ~pair();

private:
  friend class sge::shader::parameter::planar_texture;
  friend class sge::shader::scoped_pair;

  using planar_texture_sequence = std::unordered_set<sge::shader::parameter::planar_texture *>;

  sge::shader::context_ref const context_;

  sge::cg::program::object vertex_program_;

  sge::cg::program::object pixel_program_;

  sge::renderer::cg::loaded_program_unique_ptr const loaded_vertex_program_;

  sge::renderer::cg::loaded_program_unique_ptr const loaded_pixel_program_;

  planar_texture_sequence planar_textures_;

  void add_planar_texture(fcppt::reference<sge::shader::parameter::planar_texture>);

  void remove_planar_texture(
      sge::shader::parameter::planar_texture & // NOLINT(google-runtime-references)
  ); // NOLINT(google-runtime-references)
};

}

#endif
