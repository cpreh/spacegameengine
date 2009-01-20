#ifndef SGE_BULLET_SYSTEM_HPP_INCLUDED
#define SGE_BULLET_SYSTEM_HPP_INCLUDED

#include "types.hpp"
#include <sge/collision/system.hpp>
#include <sge/signals/signal.hpp>
#include <boost/scoped_ptr.hpp>

namespace sge
{
namespace bullet
{
class system : public collision::system
{
	public:
	system();
	void test_callback(collision::test_callback const &);
	sge::signals::connection const 
		register_callback(collision::callback const &);
	collision::object_ptr const create_circle(
		collision::sattelite_ptr,
		collision::unit);
	void update(time::funit delta);
	world_type &world();
	body_type &zero_body();
	~system();
	private:
	collision::test_callback test_;
	collision::callback_signal callback_signal_;

	boost::scoped_ptr<configuration_type> configuration;
	boost::scoped_ptr<dispatcher_type> dispatcher;
	boost::scoped_ptr<broadphase_type> broadphase;
	boost::scoped_ptr<constraint_solver_type> constraint_solver;
	boost::scoped_ptr<filter_callback_type> overlap_callback_;
	boost::scoped_ptr<world_type> world_;
	body_type zero_body_;
};
}
}

#endif
