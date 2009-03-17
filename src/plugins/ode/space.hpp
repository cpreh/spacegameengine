#ifndef SGE_ODE_SPACE_HPP_INCLUDED
#define SGE_ODE_SPACE_HPP_INCLUDED

#include <sge/collision/optional_rect.hpp>
#include <sge/noncopyable.hpp>
#include <ode/ode.h>

namespace sge
{
namespace ode
{
class space
{
	SGE_NONCOPYABLE(space)
public:
	explicit space(
		collision::optional_rect const &);
	dSpaceID &id();
	dSpaceID const &id() const;
	~space();
private:
	dSpaceID id_;
};
}
}

#endif
