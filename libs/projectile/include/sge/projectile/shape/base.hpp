//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PROJECTILE_SHAPE_BASE_HPP_INCLUDED
#define SGE_PROJECTILE_SHAPE_BASE_HPP_INCLUDED

#include <sge/projectile/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>

class btCollisionShape;

namespace sge::projectile::shape
{

class base
{
  FCPPT_NONMOVABLE(base);

public:
  [[nodiscard]] virtual btCollisionShape &bullet_shape() = 0;

  [[nodiscard]] virtual btCollisionShape const &bullet_shape() const = 0;

  SGE_PROJECTILE_DETAIL_SYMBOL
  virtual ~base();

protected:
  SGE_PROJECTILE_DETAIL_SYMBOL
  explicit base();
};

}

#endif
