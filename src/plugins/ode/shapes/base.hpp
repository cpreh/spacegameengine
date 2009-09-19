#ifndef SGE_ODE_SHAPES_BASE_HPP_INCLUDED
#define SGE_ODE_SHAPES_BASE_HPP_INCLUDED

#include "../group_fwd.hpp"
#include <sge/collision/shapes/base.hpp>
#include <ode/ode.h>

namespace sge
{
namespace ode
{
namespace shapes
{
class base
{
public:
	base(
		dGeomID);
	void assign_body(
		dBodyID);
	void add_to_group(
		group const &);
	~base();
protected:
	dGeomID shape_;
};
}
}
}

#endif