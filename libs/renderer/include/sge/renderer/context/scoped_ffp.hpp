//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_CONTEXT_SCOPED_FFP_HPP_INCLUDED
#define SGE_RENDERER_CONTEXT_SCOPED_FFP_HPP_INCLUDED

#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/context/ffp_unique_ptr.hpp>
#include <sge/renderer/context/scoped_ffp_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/target/base_ref.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::renderer::context
{

class scoped_ffp
{
  FCPPT_NONMOVABLE(scoped_ffp);

public:
  SGE_RENDERER_DETAIL_SYMBOL
  scoped_ffp(sge::renderer::device::ffp_ref, sge::renderer::target::base_ref);

  SGE_RENDERER_DETAIL_SYMBOL
  ~scoped_ffp();

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::context::ffp &get() const;

private:
  sge::renderer::device::ffp_ref const device_;

  sge::renderer::context::ffp_unique_ptr const context_;
};

}

#endif
