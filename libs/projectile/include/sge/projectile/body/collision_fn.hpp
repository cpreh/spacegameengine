//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_BODY_COLLISION_FN_HPP_INCLUDED
#define SGE_PROJECTILE_BODY_COLLISION_FN_HPP_INCLUDED

#include <sge/projectile/body/object_fwd.hpp>

namespace sge
{
namespace projectile
{
namespace body
{
typedef
void
collision_fn(
	object const &,
	object const &);
}
}
}

#endif
