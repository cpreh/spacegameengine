//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/projectile/impl/object_extrusion_depth.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/config/external_begin.hpp>
#include <LinearMath/btScalar.h>
#include <fcppt/config/external_end.hpp>

btScalar sge::projectile::impl::object_extrusion_depth() { return fcppt::literal<btScalar>(10); }
