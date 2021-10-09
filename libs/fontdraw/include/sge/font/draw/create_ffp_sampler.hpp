//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_FONT_DRAW_CREATE_FFP_SAMPLER_HPP_INCLUDED
#define SGE_FONT_DRAW_CREATE_FFP_SAMPLER_HPP_INCLUDED

#include <sge/font/draw/detail/symbol.hpp>
#include <sge/image/color/format_fwd.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/state/ffp/sampler/optional_object_unique_ptr.hpp>

namespace sge::font::draw
{

SGE_FONT_DRAW_DETAIL_SYMBOL
sge::renderer::state::ffp::sampler::optional_object_unique_ptr
    create_ffp_sampler(sge::renderer::device::ffp_ref, sge::image::color::format);

}

#endif
