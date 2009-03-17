#ifndef SGE_CELL_WORLD_HPP_INCLUDED
#define SGE_CELL_WORLD_HPP_INCLUDED

#include "grid.hpp"
#include "intrusive_circle_list.hpp"
#include <sge/collision/world.hpp>
#include <sge/collision/time_unit.hpp>
#include <sge/collision/optional_rect.hpp>

namespace sge
{
namespace cell
{

class circle;

class world : public collision::world {
public:
	explicit world(
		collision::optional_rect const &);

	~world();

	void
	test_callback(
		collision::test_callback const &);

	signal::auto_connection
	register_callback(
		collision::callback const &);
	
	collision::objects::circle_ptr const
	create_circle(
		collision::satellite_ptr,
		collision::point const &center,
		collision::point const &speed,
		collision::unit radius);

	void
	update(
		collision::time_unit delta);
private:
	bool call_test(
		collision::satellite const &,
		collision::satellite const &
	);

	void on_collide(
		circle &,
		circle &);

	grid grid_;
	bool test_running;
	intrusive_circle_list objects;
	collision::callback_signal sig;
	collision::test_callback test_callback_;
};

}
}

#endif
