//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/draw/create_ffp_sampler.hpp>
#include <sge/image/color/format.hpp>
#include <sge/renderer/device/ffp.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/state/ffp/sampler/alpha_op.hpp>
#include <sge/renderer/state/ffp/sampler/arg.hpp>
#include <sge/renderer/state/ffp/sampler/arg1.hpp>
#include <sge/renderer/state/ffp/sampler/color_op.hpp>
#include <sge/renderer/state/ffp/sampler/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/state/ffp/sampler/op.hpp>
#include <sge/renderer/state/ffp/sampler/optional_object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/sampler/parameters.hpp>
#include <sge/renderer/state/ffp/sampler/unary_op.hpp>
#include <sge/renderer/state/ffp/sampler/unary_op_type.hpp>

sge::renderer::state::ffp::sampler::optional_object_unique_ptr sge::font::draw::create_ffp_sampler(
    sge::renderer::device::ffp_ref const _device, sge::image::color::format const _color_format)
{
  return _color_format == sge::image::color::format::a8
             ? sge::renderer::state::ffp::sampler::optional_object_unique_ptr(
                   _device.get().create_ffp_sampler_state(
                       sge::renderer::state::ffp::sampler::parameters(
                           sge::renderer::state::ffp::sampler::color_op(
                               sge::renderer::state::ffp::sampler::op(
                                   sge::renderer::state::ffp::sampler::unary_op(
                                       sge::renderer::state::ffp::sampler::unary_op_type::arg,
                                       sge::renderer::state::ffp::sampler::arg1(
                                           sge::renderer::state::ffp::sampler::arg::
                                               vertex_color)))),
                           sge::renderer::state::ffp::sampler::alpha_op(
                               sge::renderer::state::ffp::sampler::op(
                                   sge::renderer::state::ffp::sampler::unary_op(
                                       sge::renderer::state::ffp::sampler::unary_op_type::arg,
                                       sge::renderer::state::ffp::sampler::arg1(
                                           sge::renderer::state::ffp::sampler::arg::texture)))))))
             : sge::renderer::state::ffp::sampler::optional_object_unique_ptr();
}
