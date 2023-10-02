//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/index/nonconst_tag.hpp>
#include <sge/renderer/index/view.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/index/any/make_view.hpp>
#include <sge/renderer/index/any/view.hpp>
#include <sge/renderer/index/any/detail/make_view_element.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/index/dynamic/view.hpp>
#include <fcppt/enum/to_static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

sge::renderer::index::any::view
sge::renderer::index::any::make_view(sge::renderer::index::dynamic::view const &_view)
{
  return fcppt::enum_::to_static(
      _view.format(),
      [&_view](auto const _value)
      {
        return sge::renderer::index::any::view{sge::renderer::index::any::detail::make_view_element<
            std::integral_constant<sge::renderer::index::dynamic::format, _value>,
            sge::renderer::index::nonconst_tag>{_view.data(), _view.size()}};
      });
}
