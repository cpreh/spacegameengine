#ifndef SGE_ODE_LIBRARY_HPP_INCLUDED
#define SGE_ODE_LIBRARY_HPP_INCLUDED

#include <boost/noncopyable.hpp>

namespace sge
{
namespace ode
{
class library : boost::noncopyable
{
	public:
	library();
	~library();
};
}
}

#endif
