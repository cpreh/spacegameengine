#ifndef SGE_ODE_SPACE_HPP_INCLUDED
#define SGE_ODE_SPACE_HPP_INCLUDED

#include <boost/noncopyable.hpp>
#include <ode/ode.h>

namespace sge
{
namespace ode
{
class space : boost::noncopyable
{
public:
	space();
	dSpaceID &id();
	dSpaceID const &id() const;
	~space();
private:
	dSpaceID id_;
};
}
}

#endif
