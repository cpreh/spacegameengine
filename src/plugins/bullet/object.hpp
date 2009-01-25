#ifndef SGE_BULLET_OBJECT_HPP_INCLUDED
#define SGE_BULLET_OBJECT_HPP_INCLUDED

#include "types.hpp"
#include "system_fwd.hpp"
#include "constraint.hpp"
#include "motion_state.hpp"
#include <sge/collision/point.hpp>
#include <sge/collision/unit.hpp>
#include <sge/collision/sattelite_fwd.hpp>
#include <sge/math/vector/basic_decl.hpp>

namespace sge
{
namespace bullet
{
class object
{
	public:
	object(
		system &,
		collision::sattelite_ptr,
		shape_ptr,
		unit mass);

	void pos(collision::point const &);
	collision::point const pos() const;
	void speed(collision::point const &);
	collision::point const speed() const;
	~object();
	private:
	friend class motion_state;
	void position_changed(point const &);

	collision::sattelite_ptr sat;
	world_type &world_;
	shape_ptr shape_;
	motion_state motion_state_;
	body_type body_;
	constraint constraint_;
};
}
}

#endif
