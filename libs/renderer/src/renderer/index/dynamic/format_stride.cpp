//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/size_type.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/index/dynamic/format_element.hpp>
#include <sge/renderer/index/dynamic/format_stride.hpp>
#include <fcppt/enum/to_static.hpp>

sge::renderer::size_type
sge::renderer::index::dynamic::format_stride(sge::renderer::index::dynamic::format const _format)
{
  return fcppt::enum_::to_static(
      _format,
      [](auto const _value)
      { return sizeof(typename sge::renderer::index::dynamic::format_element<_value>::type); });
}
