#ifndef SGE_ODE_WORLD_HPP_INCLUDED
#define SGE_ODE_WORLD_HPP_INCLUDED

#include <boost/noncopyable.hpp>
#include <ode/ode.h>

namespace sge
{
namespace ode
{
class world : boost::noncopyable
{
public:
	world();
	dWorldID &id();
	dWorldID const &id() const;
	~world();
private:
	dWorldID id_;
};
}
}

#endif
