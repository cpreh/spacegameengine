//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_D3DINCLUDE_HPP_INCLUDED
#define SGE_D3D9_D3DINCLUDE_HPP_INCLUDED

#include <awl/backends/windows/windows.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wpedantic)
#include <fcppt/config/external_begin.hpp>
#include <d3d9.h>
#include <fcppt/config/external_end.hpp>
FCPPT_PP_POP_WARNING

#endif
