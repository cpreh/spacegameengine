//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_FFP_ALPHA_TEST_FUNC_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_ALPHA_TEST_FUNC_HPP_INCLUDED

#include <sge/renderer/state/ffp/alpha_test/func_fwd.hpp>

namespace sge::renderer::state::ffp::alpha_test
{

enum class func
{
  never,
  less,
  equal,
  less_equal,
  greater,
  not_equal,
  greater_equal,
  always
};

}

#endif
