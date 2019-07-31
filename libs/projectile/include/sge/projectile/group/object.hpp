//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_GROUP_OBJECT_HPP_INCLUDED
#define SGE_PROJECTILE_GROUP_OBJECT_HPP_INCLUDED

#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/detail/symbol.hpp>
#include <sge/projectile/group/id.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace projectile
{
namespace group
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_PROJECTILE_DETAIL_SYMBOL explicit
	object(
		world &);

	SGE_PROJECTILE_DETAIL_SYMBOL
	~object();
private:
	friend class sge::projectile::world;

	id category_,collides_;

	void
	collides_with(
		object const &);
};
}
}
}

#endif
