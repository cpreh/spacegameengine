//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_VIEW_DATA_ANY_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_DATA_ANY_HPP_INCLUDED

#include <sge/image/mizuiro_color_traits.hpp> // IWYU pragma: keep
#include <fcppt/variant/apply.hpp>

namespace sge::image::impl::view
{

template <typename Dest, typename View>
Dest data_any(View const &_view)
{
  return fcppt::variant::apply([](auto const &_src) { return _src.data(); }, _view.get());
}

}

#endif
