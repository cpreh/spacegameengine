//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_CAC_VISITOR_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_CAC_VISITOR_HPP_INCLUDED

#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/impl/dynamic/algorithm/cac/convert.hpp>
#include <sge/image/color/impl/dynamic/algorithm/cac/copy.hpp>
#include <sge/image/color/impl/dynamic/algorithm/cac/permutate_compare.hpp>
#include <sge/image/color/impl/dynamic/view/color_layout.hpp>
#include <fcppt/not.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::image::color::impl::dynamic::algorithm::cac
{

class visitor
{
public:
  visitor(
      sge::image::algorithm::may_overlap const _overlap,
      sge::image::algorithm::uninitialized const _uninitialized)
      : overlap_{_overlap}, uninitialized_{_uninitialized}
  {
  }

  using result_type = void;

  template <typename Source, typename Dest>
  std::enable_if_t<std::is_same<typename Source::format, typename Dest::format>::value, result_type>
  operator()(Source const &_source, Dest const &_dest) const
  {
    if (sge::image::color::impl::dynamic::algorithm::cac::permutate_compare(
            sge::image::color::impl::dynamic::view::color_layout(_source),
            sge::image::color::impl::dynamic::view::color_layout(_dest)))
    {
      sge::image::color::impl::dynamic::algorithm::cac::copy(
          _source, _dest, overlap_, uninitialized_);
    }
    else
    {
      sge::image::color::impl::dynamic::algorithm::cac::convert(_source, _dest, uninitialized_);
    }
  }

  template <typename Source, typename Dest>
  std::enable_if_t<
      fcppt::not_(std::is_same<typename Source::format, typename Dest::format>::value),
      result_type>
  operator()(Source const &_source, Dest const &_dest) const
  {
    sge::image::color::impl::dynamic::algorithm::cac::convert(_source, _dest, uninitialized_);
  }

private:
  sge::image::algorithm::may_overlap overlap_;

  sge::image::algorithm::uninitialized uninitialized_;
};

}

#endif
