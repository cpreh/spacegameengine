#ifndef SGE_BULLET_WORLD_HPP_INCLUDED
#define SGE_BULLET_WORLD_HPP_INCLUDED

#include "types.hpp"
#include "overlap_callback.hpp"
#include <sge/collision/world.hpp>
#include <sge/signals/signal.hpp>
#include <boost/scoped_ptr.hpp>

namespace sge
{
namespace bullet
{
class world : public collision::world
{
public:
	world();

	void test_callback(
		collision::test_callback const &);

	sge::signals::connection const 
	register_callback(
		collision::callback const &);

	collision::objects::circle_ptr const
	create_circle(
		collision::satellite_ptr,
		collision::point const &center,
		collision::point const &speed,
		collision::unit);

	void update(
		collision::time_unit delta);

	world_type &world_internal();
	body_type &zero_body();
	~world();
private:
	collision::test_callback test_;
	collision::callback_signal callback_signal_;

	boost::scoped_ptr<configuration_type> configuration;
	boost::scoped_ptr<dispatcher_type> dispatcher;
	boost::scoped_ptr<broadphase_type> broadphase;
	boost::scoped_ptr<constraint_solver_type> constraint_solver;
	overlap_callback overlap_callback_;
	boost::scoped_ptr<world_type> world_;
	body_type zero_body_;
};
}
}

#endif
