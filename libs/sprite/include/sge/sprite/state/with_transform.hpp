//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_STATE_WITH_TRANSFORM_HPP_INCLUDED
#define SGE_SPRITE_STATE_WITH_TRANSFORM_HPP_INCLUDED

#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/optional_object_unique_ptr_fwd.hpp>
#include <sge/sprite/optional_projection_dim.hpp>
#include <sge/sprite/detail/symbol.hpp>
#include <sge/sprite/state/with_transform_fwd.hpp> // IWYU pragma: keep
#include <sge/sprite/state/roles/projection_dim.hpp>
#include <sge/sprite/state/roles/transform.hpp>
#include <fcppt/reference_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::state
{

struct with_transform
{
  using role = sge::sprite::state::roles::transform;

  using option_role = sge::sprite::state::roles::projection_dim;

  using needs_ffp = std::true_type;

  using persistent = std::false_type;

  using has_parameter = std::true_type;

  using state_type = sge::renderer::state::ffp::transform::object_unique_ptr;

  using optional_extra_option = sge::sprite::optional_projection_dim;

  SGE_SPRITE_DETAIL_SYMBOL
  static sge::renderer::state::ffp::transform::optional_object_unique_ptr make(
      sge::renderer::device::ffp_ref,
      sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
      sge::sprite::state::with_transform::optional_extra_option const &);

  SGE_SPRITE_DETAIL_SYMBOL
  static void
  set(sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
      fcppt::reference<sge::renderer::state::ffp::transform::object const>);

  SGE_SPRITE_DETAIL_SYMBOL
  static void unset(sge::renderer::context::ffp & // NOLINT(google-runtime-references)
  ); // NOLINT(google-runtime-references)
};

}

#endif
