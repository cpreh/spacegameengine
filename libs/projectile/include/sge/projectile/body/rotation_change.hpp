//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_BODY_ROTATION_CHANGE_HPP_INCLUDED
#define SGE_PROJECTILE_BODY_ROTATION_CHANGE_HPP_INCLUDED

#include <sge/projectile/body/rotation_change_fn.hpp>
#include <fcppt/function_impl.hpp>


namespace sge
{
namespace projectile
{
namespace body
{

typedef
fcppt::function<
	sge::projectile::body::rotation_change_fn
>
rotation_change;

}
}
}

#endif
