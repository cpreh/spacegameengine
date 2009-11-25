#ifndef SGE_ODE_GROUP_HPP_INCLUDED
#define SGE_ODE_GROUP_HPP_INCLUDED

#include "group_id.hpp"
#include <sge/collision/group.hpp>

namespace sge
{
namespace ode
{
class group
:
	public collision::group
{
public:
	group(
		group_id);

	void add(
		collision::body_ptr);
	void collides_with(
		group const &);

	group_id category() const;
	group_id collides() const;
private:
	group_id
		category_,
		collides_;
	bool dirty_;
};
}
}

#endif
