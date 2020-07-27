//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_GHOST_BODY_EXIT_HPP_INCLUDED
#define SGE_PROJECTILE_GHOST_BODY_EXIT_HPP_INCLUDED

#include <sge/projectile/ghost/body_exit_fn.hpp>
#include <fcppt/function_impl.hpp>


namespace sge
{
namespace projectile
{
namespace ghost
{

using
body_exit
=
fcppt::function<
	sge::projectile::ghost::body_exit_fn
>;

}
}
}

#endif
