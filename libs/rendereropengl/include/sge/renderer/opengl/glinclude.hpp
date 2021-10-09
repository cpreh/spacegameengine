//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_OPENGL_GLINCLUDE_HPP_INCLUDED
#define SGE_RENDERER_OPENGL_GLINCLUDE_HPP_INCLUDED

#include <fcppt/config/platform.hpp>
#if defined(FCPPT_CONFIG_DARWIN_PLATFORM)
#include <fcppt/config/external_begin.hpp>
#include <OpenGL/gl.h>
#include <fcppt/config/external_end.hpp>
#else
#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif
#if !defined(NOMINMAX)
#define NOMINMAX
#endif
#include <fcppt/config/external_begin.hpp>
#include <windows.h>
#include <fcppt/config/external_end.hpp>
#endif
#include <fcppt/config/external_begin.hpp>
#include <GL/gl.h>
#include <fcppt/config/external_end.hpp>
#endif

#endif
