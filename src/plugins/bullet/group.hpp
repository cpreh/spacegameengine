#ifndef SGE_BULLET_GROUP_HPP_INCLUDED
#define SGE_BULLET_GROUP_HPP_INCLUDED

#include "group_id.hpp"
#include <sge/collision/group.hpp>

namespace sge
{
namespace bullet
{
class group
:
	public collision::group
{
public:
	explicit 
	group(
		group_id);
	
	void 
	add(
		collision::shapes::base_ptr);
	
	void
	collides_with(
		group &);
	
	group_id 
	category() const;
	
	group_id 
	collides() const;
private:
	group_id 
		category_,
		collides_;
};
}
}

#endif