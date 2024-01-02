//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_ALGORITHM_PRINT_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_ALGORITHM_PRINT_IMPL_HPP_INCLUDED

#include <sge/image/mizuiro_color_traits.hpp> // IWYU pragma: keep
#include <sge/image/algorithm/print.hpp>
#include <sge/image/view/const_object.hpp>
#include <mizuiro/color/output.hpp> // IWYU pragma: keep
#include <mizuiro/image/algorithm/print.hpp>
#include <fcppt/io/ostream_fwd.hpp>
#include <fcppt/variant/apply.hpp>

template <typename Tag>
void sge::image::algorithm::print(
    fcppt::io::ostream &_ostream, sge::image::view::const_object<Tag> const &_view)
{
  fcppt::variant::apply(
      [&_ostream](auto const &_view_inner)
      { mizuiro::image::algorithm::print(_ostream, _view_inner); },
      _view.get());
}

#endif
