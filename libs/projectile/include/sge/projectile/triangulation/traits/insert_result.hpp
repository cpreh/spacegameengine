//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PROJECTILE_TRIANGULATION_TRAITS_INSERT_RESULT_HPP_INCLUDED
#define SGE_PROJECTILE_TRIANGULATION_TRAITS_INSERT_RESULT_HPP_INCLUDED

#include <sge/projectile/triangulation/default_tag.hpp>
#include <sge/projectile/triangulation/traits/insert_result_fwd.hpp> // IWYU pragma: export

namespace sge::projectile::triangulation::traits
{

template <typename Container, typename Vertex>
struct insert_result<Container, Vertex, sge::projectile::triangulation::default_tag>
{
  static void
  execute(Container &_container, Vertex const &_v1, Vertex const &_v2, Vertex const &_v3)
  {
    using value_type = typename Container::value_type;

    _container.insert(_container.end(), value_type{_v1, _v2, _v3});
  }
};

}

#endif
