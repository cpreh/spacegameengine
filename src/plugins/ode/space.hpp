#ifndef SGE_ODE_SPACE_HPP_INCLUDED
#define SGE_ODE_SPACE_HPP_INCLUDED

#include <sge/collision/rect.hpp>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <ode/ode.h>

namespace sge
{
namespace ode
{
class space : boost::noncopyable
{
public:
	space(
		boost::optional<collision::rect> const &);
	dSpaceID &id();
	dSpaceID const &id() const;
	~space();
private:
	dSpaceID id_;
};
}
}

#endif
