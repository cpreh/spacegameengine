#ifndef SGE_ODE_LIBRARY_HPP_INCLUDED
#define SGE_ODE_LIBRARY_HPP_INCLUDED

#include <sge/noncopyable.hpp>

namespace sge
{
namespace ode
{
class library
{
	SGE_NONCOPYABLE(library)
	public:
	library();
	~library();
};
}
}

#endif
