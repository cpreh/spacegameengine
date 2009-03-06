#ifndef SGE_CELL_CIRCLE_HPP_INCLUDED
#define SGE_CELL_CIRCLE_HPP_INCLUDED

#include <sge/collision/objects/circle.hpp>
#include <sge/collision/callbacks.hpp>

namespace sge
{
namespace cell
{

class grid;

class circle : public collision::circle {
public:
	circle(
		satellite_ptr,
		point const &center,
		point const &speed,
		unit radius,
		grid &,
		collision::test_callback const &,
		collision::callback_signal &);
	
	void center(point const &);
	point const center() const;
	void speed(point const &);
	point const speed() const;

	void update(
		time::funit);

	~circle();
private:
	void reposition();

	satellite_ptr sat_;

	poinr center_,
	      speed_;
	unit const radius_;

	grid &grid_;
	backlink_list backlinks;
	collision::test_callback const test_callback;
	collision::callback_signal &callback;
};

}
}

#endif
