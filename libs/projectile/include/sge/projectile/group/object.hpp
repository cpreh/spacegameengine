//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_GROUP_OBJECT_HPP_INCLUDED
#define SGE_PROJECTILE_GROUP_OBJECT_HPP_INCLUDED

#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/detail/symbol.hpp>
#include <sge/projectile/group/id.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::projectile::group
{

class object
{
	FCPPT_NONMOVABLE(
		object
	);
public:
	SGE_PROJECTILE_DETAIL_SYMBOL
	explicit
	object(
		sge::projectile::world & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)

	SGE_PROJECTILE_DETAIL_SYMBOL
	~object(); // NOLINT(performance-trivially-destructible)
private:
	friend class sge::projectile::world;

	sge::projectile::group::id category_;

	sge::projectile::group::id collides_;

	void
	collides_with(
		sge::projectile::group::object const &
	);
};

}

#endif
