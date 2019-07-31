//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_GHOST_SCOPED_HPP_INCLUDED
#define SGE_PROJECTILE_GHOST_SCOPED_HPP_INCLUDED

#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/detail/symbol.hpp>
#include <sge/projectile/ghost/object_fwd.hpp>
#include <sge/projectile/ghost/scoped_fwd.hpp>
#include <sge/projectile/group/sequence.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace projectile
{
namespace ghost
{
class scoped
{
FCPPT_NONCOPYABLE(
	scoped);
public:
	SGE_PROJECTILE_DETAIL_SYMBOL explicit
	scoped(
		world &,
		object &,
		group::sequence const &);

	SGE_PROJECTILE_DETAIL_SYMBOL ~scoped();
private:
	world &world_;
	object &object_;
};
}
}
}

#endif
