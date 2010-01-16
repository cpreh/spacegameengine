#include "../../shapes/box.hpp"
#include "../../convert/to_bullet.hpp"
#include "../../convert/dim_to_sge.hpp"
#include "../../log.hpp"
#include <sge/exception.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/text.hpp>

namespace
{
fcppt::log::object 
mylogger(
	fcppt::log::parameters::inherited(
		sge::bullet::log(),
		FCPPT_TEXT("shapes: box")));
}

sge::bullet::shapes::box::box(
	collision::satellite_ptr _satellite,
	collision::constraint::type _constraint,
	sge::bullet::world &_world,
	collision::point const &_position,
	collision::solidity::type const _solidity,
	collision::dim const &_dim)
:
	base(
		bullet_shape_ptr(
			new btBoxShape(
				// btBoxShape wants _halfdimensions_, so 1/2 here
				convert::to_bullet(
					_dim/
					static_cast<unit>(2)))),
		_satellite,
		_constraint,
		_world,
		_position,
		_solidity)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("Added a box with halfdimensions: ")
			<< (_dim/static_cast<unit>(2)));
			
}

sge::collision::dim const 
sge::bullet::shapes::box::dim() const
{
	return 
		convert::dim_to_sge(
			// NOTE: what margin? collision margin?
			dynamic_cast<btBoxShape &>(*shape_).getHalfExtentsWithoutMargin()); 
}

void 
sge::bullet::shapes::box::dim(
	collision::dim const &)
{
	throw 
		sge::exception(
			FCPPT_TEXT("changing the dimensions of a box dynamically is not supported by bullet-2.75 (last version checked)"));
}
