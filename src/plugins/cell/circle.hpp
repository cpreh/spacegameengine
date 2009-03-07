#ifndef SGE_CELL_CIRCLE_HPP_INCLUDED
#define SGE_CELL_CIRCLE_HPP_INCLUDED

#include "backlink_list.hpp"
#include "register_callback.hpp"
#include "unregister_callback.hpp"
#include "circle_list.hpp"
#include <sge/collision/objects/circle.hpp>
#include <sge/collision/callbacks.hpp>
#include <sge/collision/satellite_fwd.hpp>
#include <sge/math/vector/basic_decl.hpp>
#include <sge/time/funit.hpp>

namespace sge
{
namespace cell
{

class grid;

class circle : public collision::objects::circle {
public:
	circle(
		collision::satellite_ptr,
		collision::point const &center,
		collision::point const &speed,
		collision::unit radius,
		grid &,
		collision::test_callback const &,
		collision::callback_signal &,
		register_callback const &,
		unregister_callback const &);
	
	void center(
		collision::point const &);
	
	collision::point const
	center() const;

	void speed(
		collision::point const &);
	
	collision::point const
	speed() const;

	collision::unit radius() const;
	collision::satellite &satellite();

	void update(
		time::funit);

	~circle();
private:
	void reposition();

	collision::satellite_ptr sat;

	collision::point
		center_,
		speed_;
	collision::unit const radius_;

	grid &grid_;
	backlink_list backlinks;
	collision::test_callback const test_callback;
	collision::callback_signal &callback;
	register_callback const register_;
	unregister_callback const unregister_;
	circle_list::iterator const list_pos;
};

}
}

#endif
