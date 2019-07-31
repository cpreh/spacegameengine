//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_AUDIO_LOADER_UNIQUE_PTR_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_AUDIO_LOADER_UNIQUE_PTR_HPP_INCLUDED

#include <sge/systems/impl/audio/loader_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace systems
{
namespace impl
{
namespace audio
{

typedef
fcppt::unique_ptr<
	sge::systems::impl::audio::loader
>
loader_unique_ptr;

}
}
}
}

#endif
