//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_INDEX_ANY_GENERATE_HPP_INCLUDED
#define SGE_RENDERER_INDEX_ANY_GENERATE_HPP_INCLUDED

#include <sge/renderer/index/iterator.hpp> // IWYU pragma: keep
#include <sge/renderer/index/view.hpp> // IWYU pragma: keep
#include <sge/renderer/index/any/view.hpp>
#include <fcppt/tag.hpp>
#include <fcppt/variant/apply.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer::index::any
{

template <typename Gen>
void generate(sge::renderer::index::any::view const &_view, Gen const &_gen)
{
  fcppt::variant::apply(
      [&_gen](auto const &_inner_view)
      {
        for (auto item : _inner_view)
        {
          item.set(
              _gen(fcppt::tag<typename std::remove_cvref_t<decltype(_inner_view)>::value_type>{}));
        }
      },
      _view);
}

}

#endif
