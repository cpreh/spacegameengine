//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_BUFFERS_MULTI_DECL_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_MULTI_DECL_HPP_INCLUDED

#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/vertex/const_declaration_ref.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/multi_fwd.hpp> // IWYU pragma: keep
#include <sge/sprite/buffers/object.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/slice_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::buffers
{

template <typename Choices>
class multi
{
  FCPPT_NONMOVABLE(multi);

public:
  using choices = Choices;

  multi(
      sge::renderer::device::core_ref,
      sge::renderer::vertex::const_declaration_ref,
      sge::sprite::buffers::option);

  ~multi();

  using slice_type = sge::sprite::buffers::slice<Choices>;

  [[nodiscard]] slice_type allocate(sge::sprite::count);

  [[nodiscard]] sge::renderer::vertex::declaration const &vertex_declaration() const;

private:
  sge::renderer::device::core_ref const renderer_;

  sge::renderer::vertex::const_declaration_ref const vertex_declaration_;

  sge::sprite::buffers::option const buffers_option_;

  using buffers_object = sge::sprite::buffers::object<Choices>;

  using buffer_vector = std::vector<fcppt::unique_ptr<buffers_object>>;

  buffer_vector buffers_;
};

}

#endif
