//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_FFP_ALPHA_TEST_ENABLED_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_ALPHA_TEST_ENABLED_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/alpha_test/enabled_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/state/ffp/alpha_test/func.hpp>
#include <sge/renderer/state/ffp/alpha_test/ref.hpp>

namespace sge::renderer::state::ffp::alpha_test
{

class enabled
{
public:
  SGE_RENDERER_DETAIL_SYMBOL
  enabled(sge::renderer::state::ffp::alpha_test::func, sge::renderer::state::ffp::alpha_test::ref);

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::state::ffp::alpha_test::func func() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::state::ffp::alpha_test::ref ref() const;

private:
  sge::renderer::state::ffp::alpha_test::func func_;

  sge::renderer::state::ffp::alpha_test::ref ref_;
};

}

#endif
