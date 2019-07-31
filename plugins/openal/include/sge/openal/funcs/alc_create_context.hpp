//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENAL_FUNCS_ALC_CREATE_CONTEXT_HPP_INCLUDED
#define SGE_OPENAL_FUNCS_ALC_CREATE_CONTEXT_HPP_INCLUDED

#include <sge/openal/alc.hpp>


namespace sge
{
namespace openal
{
namespace funcs
{

ALCcontext *
alc_create_context(
	ALCdevice &
);

}
}
}

#endif
