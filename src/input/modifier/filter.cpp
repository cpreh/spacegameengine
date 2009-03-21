#include "list.hpp"
#include <sge/input/modifier/filter.hpp>
#include <sge/input/modifier/states.hpp>
#include <sge/input/system.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/container/map_impl.hpp>
#include <sge/assert.hpp>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>

sge::input::modifier::filter::filter(sge::input::system_ptr const is)
:
	signal(),
	repeat_signal(),
	ic(
		is->register_callback(
			boost::bind(&filter::input_callback,this,_1))),
	irc(
		is->register_repeat_callback(
			boost::bind(&filter::input_repeat_callback,this,_1))),
	modifiers()
{
	BOOST_FOREACH(object const &o,list())
		BOOST_FOREACH(key_code const &c,o.codes)
			modifiers.insert(c,static_cast<key_state>(0));
}

sge::signal::auto_connection sge::input::modifier::filter::register_callback(
	callback_type const &f)
{
	return signal.connect(f);
}

sge::signal::auto_connection sge::input::modifier::filter::register_repeat_callback(
	repeat_callback_type const &f)
{
	return repeat_signal.connect(f);
}

void sge::input::modifier::filter::input_callback(key_pair const &k)
{
	BOOST_FOREACH(object const &o,list())
	{
		BOOST_FOREACH(key_code const &c,o.codes)
		{
			if (c == k.key().code())
			{
				modifiers[k.key().code()] = k.value();
				return;
			}
		}
	}

	signal(k,modifiers);
}

void sge::input::modifier::filter::input_repeat_callback(key_type const &k)
{
	repeat_signal(k,modifiers);
}
