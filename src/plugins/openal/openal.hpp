#ifndef SGE_OPENAL_OPENAL_HPP_INCLUDED
#define SGE_OPENAL_OPENAL_HPP_INCLUDED

#include <sge/config.h>
#if defined(SGE_WINDOWS_PLATFORM) || defined(SGE_DARWIN_PLATFORM)
#include <al.h>
#include <alc.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#endif

#endif
