#ifndef SGE_ODE_GEOM_HPP_INCLUDED
#define SGE_ODE_GEOM_HPP_INCLUDED

#include "body_fwd.hpp"
#include <sge/noncopyable.hpp>
#include <ode/ode.h>

namespace sge
{
namespace ode
{
class geom
{
	SGE_NONCOPYABLE(geom)
public:
	geom(
		dGeomID,
		body &);
	dGeomID &id();
	dGeomID const &id() const;
	~geom();
private:
	dGeomID id_;
};
}
}

#endif
