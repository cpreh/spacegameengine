/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/iostream.hpp>
#include <sge/media.hpp>
#include <sge/math/matrix_impl.hpp>
#include <sge/signals/scoped_connection.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/audio/player.hpp>
#include <sge/log/headers.hpp>
#include <sge/audio/listener.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/sound.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/input/system.hpp>
#include <sge/input/key_type.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/image/loader.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/texture_animation.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/util.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/default_creator.hpp>
#include <sge/texture/default_creator_impl.hpp>
#include <sge/signals/signal.hpp>
#include <sge/input/classification.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/container/map.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/if.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/foreach.hpp>
#include <exception>
#include <ostream>
#include <cstdlib>
#include <map>

namespace
{
namespace modifiers
{
enum type { shift,ctrl,alt };
}
typedef sge::container::map<
	std::map,
	sge::input::key_code,
	sge::input::key_state> modifier_states;

class modifier_filter
{
	public:
	typedef void fn_callback_type (sge::input::key_pair const &,modifier_states const &);
	typedef boost::function<fn_callback_type> callback_type;

	explicit modifier_filter(sge::input::system_ptr const is)
	{
		is->register_callback(
			boost::bind(&modifier_filter::input_callback,this,_1));

		using namespace sge::input::kc;

		std::vector<sge::input::key_code> const codes = 
			boost::assign::list_of
			(key_lshift)(key_rshift)
			(key_lctrl)(key_rctrl)
			(key_alt)(key_altgr);

		BOOST_FOREACH(sge::input::key_code const c,codes)
			modifiers.insert(c,static_cast<sge::input::key_state>(0));
	}

	sge::signals::scoped_connection const register_callback(
		callback_type const &f)
	{
		return signal.connect(f);
	}
	private:
	sge::signals::signal<fn_callback_type> signal;
	modifier_states modifiers;

	void input_callback(sge::input::key_pair const &k)
	{
		sge::cerr << "got " << k.key().char_code() << "\n";
		if (sge::input::is_shift(k.key().code()) || 
		    sge::input::is_ctrl(k.key().code())  ||
				sge::input::is_alt(k.key().code()))
		{
			modifiers[k.key().code()] = k.value();
			return;
		}

		signal(k,modifiers);
	}
};

void mod_callback(sge::input::key_pair const &kp,modifier_states const &mods)
{
	if (mods[sge::input::kc::key_lshift])
		sge::cerr << SGE_TEXT("S-");

	if (mods[sge::input::kc::key_lctrl])
		sge::cerr << SGE_TEXT("C-");

	if (mods[sge::input::kc::key_alt])
		sge::cerr << SGE_TEXT("A-");
	
	sge::cerr << kp.key().char_code() << SGE_TEXT("\n");
}
}

int main()
try
{
	sge::log::global().activate_hierarchy(
		sge::log::level::debug);

	sge::renderer::screen_size_t const screen_size(1024,768);

	sge::systems::instance sys(
		sge::systems::list()
		(sge::window::parameters(
			SGE_TEXT("sge modifier test")
		))
		(sge::renderer::parameters(
			sge::renderer::display_mode(
				screen_size,
				sge::renderer::bit_depth::depth32,
				sge::renderer::refresh_rate_dont_care),
			sge::renderer::depth_buffer::off,
			sge::renderer::stencil_buffer::off,
			sge::renderer::window_mode::windowed))
		(sge::systems::parameterless::input));
	
	using boost::lambda::var;
	using boost::lambda::bind;
	using boost::lambda::if_;

	bool running = true;

	sge::signals::scoped_connection const cb(
		sys.input_system()->register_callback(
			if_(bind(&sge::input::key_type::code,
				bind(&sge::input::key_pair::key,boost::lambda::_1))
			== sge::input::kc::key_escape)
		[var(running)=false])
	);

	modifier_filter mf(sys.input_system());

	sge::signals::scoped_connection const pc(
		mf.register_callback(&mod_callback));

	while(running)
	{
		sge::mainloop::dispatch();
		sge::renderer::scoped_block const block_(sys.renderer());
	}
}
catch(sge::exception const &e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
