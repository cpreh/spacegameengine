//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_INDEX_SCOPED_LOCK_HPP_INCLUDED
#define SGE_RENDERER_INDEX_SCOPED_LOCK_HPP_INCLUDED

#include <sge/renderer/lock_mode_fwd.hpp>
#include <sge/renderer/buffer/scoped_lock.hpp>
#include <sge/renderer/buffer/detail/declare_scoped_lock.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/index/buffer_ref.hpp>
#include <sge/renderer/index/scoped_lock_fwd.hpp>
#include <sge/renderer/index/tag.hpp>
#include <sge/renderer/index/dynamic/view.hpp> // IWYU pragma: keep
#include <sge/renderer/index/traits/dimension.hpp> // IWYU pragma: keep
#include <sge/renderer/index/traits/view_fwd.hpp> // IWYU pragma: keep
#include <fcppt/nonmovable.hpp>

SGE_RENDERER_BUFFER_DETAIL_DECLARE_SCOPED_LOCK(sge::renderer::index::tag);

namespace sge::renderer::index
{

class scoped_lock
{
  FCPPT_NONMOVABLE(scoped_lock);

public:
  using impl = sge::renderer::buffer::scoped_lock<sge::renderer::index::tag>;

  using lock_area = impl::lock_area;

  using view = impl::view;

  SGE_RENDERER_DETAIL_SYMBOL
  scoped_lock(sge::renderer::index::buffer_ref, sge::renderer::lock_mode);

  SGE_RENDERER_DETAIL_SYMBOL
  scoped_lock(sge::renderer::index::buffer_ref, lock_area const &, sge::renderer::lock_mode);

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL view value() const;

  SGE_RENDERER_DETAIL_SYMBOL
  ~scoped_lock();

private:
  impl impl_;
};

}

#endif
