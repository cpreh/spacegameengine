//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_AUDIO_LOADER_PLUGIN_ITERATOR_FWD_HPP_INCLUDED
#define SGE_AUDIO_LOADER_PLUGIN_ITERATOR_FWD_HPP_INCLUDED

#include <sge/audio/loader_fwd.hpp>
#include <sge/plugin/iterator_fwd.hpp>


namespace sge
{
namespace audio
{
namespace loader_plugin
{

typedef
sge::plugin::iterator<
	sge::audio::loader
>
iterator;

}
}
}

#endif
