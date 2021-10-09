//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/state/render_vector.hpp>
#include <sge/d3d9/state/ffp/alpha_test/make_states.hpp>
#include <sge/d3d9/state/ffp/alpha_test/visitor.hpp>
#include <sge/renderer/state/ffp/alpha_test/parameters.hpp>
#include <fcppt/variant/apply.hpp>

sge::d3d9::state::render_vector sge::d3d9::state::ffp::alpha_test::make_states(
    sge::renderer::state::ffp::alpha_test::parameters const &_parameters)
{
  return fcppt::variant::apply(sge::d3d9::state::ffp::alpha_test::visitor(), _parameters.variant());
}
