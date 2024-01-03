//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_ELEMENT_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_ELEMENT_HPP_INCLUDED

#include <sge/renderer/vf/color_fwd.hpp>
#include <sge/renderer/vf/element_count_type.hpp>
#include <sge/renderer/vf/extra_fwd.hpp>
#include <sge/renderer/vf/normal_fwd.hpp>
#include <sge/renderer/vf/pos_fwd.hpp>
#include <sge/renderer/vf/texpos_fwd.hpp>
#include <sge/renderer/vf/dynamic/any.hpp>
#include <sge/renderer/vf/dynamic/element.hpp>
#include <sge/renderer/vf/dynamic/extra.hpp>
#include <sge/renderer/vf/dynamic/extra_any.hpp>
#include <sge/renderer/vf/dynamic/index.hpp>
#include <sge/renderer/vf/dynamic/normal.hpp>
#include <sge/renderer/vf/dynamic/pos.hpp>
#include <sge/renderer/vf/dynamic/texpos.hpp>
#include <sge/renderer/vf/dynamic/detail/format_to_element.hpp>
#include <sge/renderer/vf/dynamic/detail/make_color.hpp>
#include <sge/renderer/vf/dynamic/detail/make_extra_element.hpp>
#include <sge/renderer/vf/dynamic/detail/make_vector.hpp>

namespace sge::renderer::vf::dynamic::detail
{

template <typename Format, sge::renderer::vf::element_count_type NumSubElements>
inline sge::renderer::vf::dynamic::element
make_element(sge::renderer::vf::pos<Format, NumSubElements> const &)
{
  return sge::renderer::vf::dynamic::element(
      sge::renderer::vf::dynamic::any{sge::renderer::vf::dynamic::pos(
          sge::renderer::vf::dynamic::detail::make_vector<Format, NumSubElements>())});
}

template <typename Format>
inline sge::renderer::vf::dynamic::element make_element(sge::renderer::vf::normal<Format> const &)
{
  return sge::renderer::vf::dynamic::element(
      sge::renderer::vf::dynamic::any{sge::renderer::vf::dynamic::normal(
          sge::renderer::vf::dynamic::detail::format_to_element<Format>::value)});
}

template <typename Format>
inline sge::renderer::vf::dynamic::element make_element(sge::renderer::vf::color<Format> const &)
{
  return sge::renderer::vf::dynamic::element(
      sge::renderer::vf::dynamic::any{sge::renderer::vf::dynamic::detail::make_color<Format>()});
}

template <typename Format, sge::renderer::vf::element_count_type NumSubElements, typename Index>
inline sge::renderer::vf::dynamic::element
make_element(sge::renderer::vf::texpos<Format, NumSubElements, Index> const &)
{
  return sge::renderer::vf::dynamic::element(
      sge::renderer::vf::dynamic::any{sge::renderer::vf::dynamic::texpos(
          sge::renderer::vf::dynamic::detail::make_vector<Format, NumSubElements>(),
          sge::renderer::vf::dynamic::index(Index::value))});
}

template <typename Format, typename Index>
inline sge::renderer::vf::dynamic::element
make_element(sge::renderer::vf::extra<Format, Index> const &)
{
  return sge::renderer::vf::dynamic::element(
      sge::renderer::vf::dynamic::any{sge::renderer::vf::dynamic::extra(
          sge::renderer::vf::dynamic::extra_any(
              sge::renderer::vf::dynamic::detail::make_extra_element(Format())),
          sge::renderer::vf::dynamic::index(Index::value))});
}

}

#endif
