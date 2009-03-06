#ifndef SGE_CELL_WORLD_HPP_INCLUDED
#define SGE_CELL_WORLD_HPP_INCLUDED

#include <sge/collision/world.hpp>

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
		callback const &);
	
	objects::circle_ptr const
	create_circle(
		sattelite_ptr,
		point const &center,
		point const &speed,
		unit radius);

	void
	update(
		time::funit delta);
private:
	bool call_test(
		collision::satellite &,
		collision::satellite &
	);

	grid grid_;
	collision::test_callback test_callback;
};

}
}

#endif
