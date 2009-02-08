#include "list.hpp"
#include <sge/input/key_code.hpp>
#include <boost/assign/list_of.hpp>

sge::input::modifier::container const &sge::input::modifier::list()
{
	static container mods = 
		boost::assign::list_of
		(object(
				boost::assign::list_of
					(sge::input::kc::key_lshift)
					(sge::input::kc::key_rshift),
				types::shift))
		(object(
				boost::assign::list_of
					(sge::input::kc::key_lctrl)
					(sge::input::kc::key_rctrl),
				types::ctrl))
		(object(
				boost::assign::list_of
					(sge::input::kc::key_alt)
					(sge::input::kc::key_altgr),
				types::alt)).to_container(mods);
	return mods;
}
