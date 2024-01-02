//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_CAC_CONVERT_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_CAC_CONVERT_HPP_INCLUDED

#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/impl/dynamic/algorithm/cac/choose.hpp>
#include <sge/image/color/impl/dynamic/algorithm/cac/convert_visitor.hpp>
#include <sge/image/color/impl/dynamic/algorithm/cac/function.hpp>
#include <sge/image/color/impl/dynamic/view/image_format.hpp>
#include <sge/image/impl/algorithm/convert_uninitialized.hpp>
#include <mizuiro/image/algorithm/make_iterator_identity.hpp>
#include <mizuiro/image/algorithm/transform.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace sge::image::color::impl::dynamic::algorithm::cac
{

// Unreachable code?
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4702)

template <typename Source, typename Dest>
inline void convert(
    Source const &_source,
    Dest const &_dest,
    sge::image::algorithm::uninitialized const _uninitialized)
{
  mizuiro::image::algorithm::transform(
      _source,
      _dest,
      sge::image::color::impl::dynamic::algorithm::cac::convert_visitor<
          sge::image::color::impl::dynamic::algorithm::cac::
              function<typename Source::format, typename Dest::format>>(
          sge::image::color::impl::dynamic::algorithm::cac::choose(
              sge::image::color::impl::dynamic::view::image_format(_source),
              sge::image::color::impl::dynamic::view::image_format(_dest))),
      mizuiro::image::algorithm::make_iterator_identity{},
      sge::image::impl::algorithm::convert_uninitialized(_uninitialized));
}

FCPPT_PP_POP_WARNING

}

#endif
