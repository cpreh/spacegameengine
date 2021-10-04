//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_BODY_SCOPED_HPP_INCLUDED
#define SGE_PROJECTILE_BODY_SCOPED_HPP_INCLUDED

#include <sge/projectile/world_ref.hpp>
#include <sge/projectile/body/object_ref.hpp>
#include <sge/projectile/body/scoped_fwd.hpp>
#include <sge/projectile/detail/symbol.hpp>
#include <sge/projectile/group/sequence.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::projectile::body
{

class scoped
{
	FCPPT_NONMOVABLE(
		scoped
	);
public:
	SGE_PROJECTILE_DETAIL_SYMBOL
	scoped(
		sge::projectile::world_ref,
		sge::projectile::body::object_ref,
		sge::projectile::group::sequence const &
	);

	SGE_PROJECTILE_DETAIL_SYMBOL
	~scoped();
private:
	sge::projectile::world_ref const world_;

	sge::projectile::body::object_ref const object_;
};

}

#endif
