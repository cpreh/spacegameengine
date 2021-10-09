//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PLUGIN_FLAGS_HPP_INCLUDED
#define SGE_PLUGIN_FLAGS_HPP_INCLUDED

#include <sge/plugin/flags_fwd.hpp>

namespace sge::plugin
{

enum class flags
{
  /**
	\brief This plugin must be unloaded after everything else has been
	cleaned up

	As an example, x11input uses libXi which hooks into the X11 display but
	has no cleanup function. If x11input gets unloaded before the display,
	then closing the display will crash.
	*/
  delayed_unload,
  fcppt_maximum = delayed_unload
};

}

#endif
