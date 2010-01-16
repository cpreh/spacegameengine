#include "../log.hpp"
#include <sge/log/global.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
//#include <fcppt/log/activate_levels.hpp>
#include <fcppt/text.hpp>

fcppt::log::object &
sge::bullet::log()
{
	static fcppt::log::object o(
		fcppt::log::parameters::inherited(
			sge::log::global(),
			FCPPT_TEXT("bullet")));
	o.enable(
		true);
			/*
	fcppt::log::activate_levels(
		o,
		fcppt::log::level::debug);
		*/
	return o;
}
