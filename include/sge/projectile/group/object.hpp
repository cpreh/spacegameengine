#ifndef SGE_PROJECTILE_GROUP_OBJECT_HPP_INCLUDED
#define SGE_PROJECTILE_GROUP_OBJECT_HPP_INCLUDED

#include <sge/projectile/group/id.hpp>
#include <sge/projectile/symbol.hpp>
#include <sge/projectile/body/object_fwd.hpp>
#include <sge/projectile/ghost/object_fwd.hpp>
#include <sge/projectile/world_fwd.hpp>
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
	SGE_PROJECTILE_SYMBOL explicit
	object(
		world &);

	SGE_PROJECTILE_SYMBOL void
	add_body(
		body::object &);

	SGE_PROJECTILE_SYMBOL void
	add_ghost(
		ghost::object &);

	SGE_PROJECTILE_SYMBOL 
	~object();
private:
	friend class sge::projectile::world;

	id category_,collides_;
	bool dirty_;

	void
	collides_with(
		object const &);
};
}
}
}

#endif
