//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_BUFFERS_WITH_DECLARATION_DECL_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_WITH_DECLARATION_DECL_HPP_INCLUDED

#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/with_declaration_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::sprite::buffers
{

template <typename Buffers>
class with_declaration
{
  FCPPT_NONMOVABLE(with_declaration);

public:
  with_declaration(sge::renderer::device::core_ref, sge::sprite::buffers::option);

  ~with_declaration();

  using buffers_type = Buffers;

  using choices = typename buffers_type::choices;

  using slice_type = typename buffers_type::slice_type;

  [[nodiscard]] slice_type allocate(sge::sprite::count);

  [[nodiscard]] buffers_type &impl();

  [[nodiscard]] buffers_type const &impl() const;

  [[nodiscard]] sge::renderer::vertex::declaration const &vertex_declaration() const;

private:
  sge::renderer::vertex::declaration_unique_ptr const vertex_declaration_;

  buffers_type buffers_;
};

}

#endif
