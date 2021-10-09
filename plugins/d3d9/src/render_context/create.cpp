//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/render_context/create.hpp>
#include <sge/d3d9/render_context/object.hpp>
#include <sge/d3d9/render_context/parameters_fwd.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/ffp_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>

sge::renderer::context::ffp_unique_ptr
sge::d3d9::render_context::create(sge::d3d9::render_context::parameters const &_parameters)
{
  return fcppt::unique_ptr_to_base<sge::renderer::context::ffp>(
      fcppt::make_unique_ptr<sge::d3d9::render_context::object>(_parameters));
}
