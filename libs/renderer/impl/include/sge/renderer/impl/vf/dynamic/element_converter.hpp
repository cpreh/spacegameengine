//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_IMPL_VF_DYNAMIC_ELEMENT_CONVERTER_HPP_INCLUDED
#define SGE_RENDERER_IMPL_VF_DYNAMIC_ELEMENT_CONVERTER_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/impl/vf/dynamic/element_converter_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/impl/vf/dynamic/lock_interval.hpp>
#include <sge/renderer/impl/vf/dynamic/unlock.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vf/dynamic/offset.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace sge::renderer::impl::vf::dynamic
{

class element_converter
{
public:
  FCPPT_DECLARE_STRONG_TYPEDEF(sge::image::color::format, original_format);

  FCPPT_DECLARE_STRONG_TYPEDEF(sge::image::color::format, backend_format);

  element_converter(
      original_format,
      backend_format,
      sge::renderer::vf::dynamic::stride,
      sge::renderer::vf::dynamic::offset);

  void convert(
      sge::renderer::impl::vf::dynamic::lock_interval const &,
      sge::renderer::raw_pointer data,
      sge::renderer::vertex::first,
      sge::renderer::impl::vf::dynamic::unlock) const;

private:
  original_format original_format_;

  backend_format backend_format_;

  sge::renderer::vf::dynamic::stride stride_;

  sge::renderer::vf::dynamic::offset offset_;
};

}

#endif
