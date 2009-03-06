#ifndef SGE_CELL_WORLD_HPP_INCLUDED
#define SGE_CELL_WORLD_HPP_INCLUDED

#include "grid.hpp"
#include <sge/collision/world.hpp>
#include <sge/collision/optional_rect.hpp>

namespace sge
{
namespace cell
{

class world : public collision::world {
public:
	explicit world(
		collision::optional_rect const &);

	void
	test_callback(
		::sge::collision::test_callback const &);

	signals::connection const 
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
		time::funit delta);
private:
	bool call_test(
		collision::satellite &,
		collision::satellite &
	);

	grid grid_;
	collision::callback_signal sig;
	collision::test_callback test_callback_;
};

}
}

#endif
