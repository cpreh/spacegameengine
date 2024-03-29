//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VERTEX_CONST_SCOPED_LOCK_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_CONST_SCOPED_LOCK_HPP_INCLUDED

#include <sge/renderer/buffer/const_scoped_lock.hpp>
#include <sge/renderer/buffer/detail/declare_const_scoped_lock.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vertex/const_buffer_ref.hpp>
#include <sge/renderer/vertex/const_scoped_lock_fwd.hpp>
#include <sge/renderer/vertex/tag.hpp>
#include <sge/renderer/vertex/traits/const_view_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/vertex/traits/dimension.hpp> // IWYU pragma: keep
#include <sge/renderer/vf/dynamic/const_view.hpp> // IWYU pragma: keep
#include <fcppt/nonmovable.hpp>

SGE_RENDERER_BUFFER_DETAIL_DECLARE_CONST_SCOPED_LOCK(sge::renderer::vertex::tag);

namespace sge::renderer::vertex
{

class const_scoped_lock
{
  FCPPT_NONMOVABLE(const_scoped_lock);

public:
  using impl = sge::renderer::buffer::const_scoped_lock<sge::renderer::vertex::tag>;

  using lock_area = impl::lock_area;

  using view = impl::const_view;

  SGE_RENDERER_DETAIL_SYMBOL
  explicit const_scoped_lock(sge::renderer::vertex::const_buffer_ref);

  SGE_RENDERER_DETAIL_SYMBOL
  const_scoped_lock(sge::renderer::vertex::const_buffer_ref, lock_area const &);

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL view value() const;

  SGE_RENDERER_DETAIL_SYMBOL
  ~const_scoped_lock();

private:
  impl impl_;
};

}

#endif
