#ifndef SGE_COLLISION_SYSTEM_HPP_INCLUDED
#define SGE_COLLISION_SYSTEM_HPP_INCLUDED

#include "system_fwd.hpp"
#include "types.hpp"
#include "callbacks.hpp"
#include "object_fwd.hpp"
#include "sattelite_fwd.hpp"
#include "../export.hpp"
#include <sge/time/types.hpp>
#include <sge/signals/connection.hpp>
#include <boost/noncopyable.hpp>

namespace sge
{
namespace collision
{
class SGE_CLASS_SYMBOL system : public boost::noncopyable
{
	public:
	SGE_SYMBOL system(test_callback const &);
	virtual sge::signals::connection const 
		register_callback(callback const &) = 0;
	virtual object_ptr const create_circle(sattelite_ptr,unit radius) = 0;
	virtual void update(time::funit delta) = 0;
	SGE_SYMBOL virtual ~system();
	protected:
	SGE_SYMBOL bool test(sattelite const &,sattelite const &);
	private:
	test_callback test_;
};
}
}

#endif
