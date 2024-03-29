//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_VIEW_SUB_ANY_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_SUB_ANY_HPP_INCLUDED

#include <sge/image/box.hpp> // IWYU pragma: keep
#include <sge/image/mizuiro_color_traits.hpp> // IWYU pragma: keep
#include <sge/image/impl/to_mizuiro_dim.hpp>
#include <sge/image/view/wrap.hpp>
#include <mizuiro/image/sub_view.hpp>
#include <fcppt/math/vector/to_dim.hpp>
#include <fcppt/variant/apply.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::image::impl::view
{

template <typename View, typename Box>
View sub_any(View const &_view, Box const &_box)
{
  return fcppt::variant::apply(
      [&_box](auto const &_src)
      {
        using source_type = std::decay_t<decltype(_src)>;

        using bound_type = typename source_type::bound_type;

        return View(sge::image::view::wrap(mizuiro::image::sub_view(
            _src,
            bound_type{
                typename bound_type::pos_t{
                    sge::image::impl::to_mizuiro_dim(fcppt::math::vector::to_dim(_box.pos()))},
                typename bound_type::size_t{sge::image::impl::to_mizuiro_dim(_box.size())}})));
      },
      _view.get());
}

}

#endif
