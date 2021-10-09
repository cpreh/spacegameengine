//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_AUDIO_FILE_EXCEPTION_HPP_INCLUDED
#define SGE_AUDIO_FILE_EXCEPTION_HPP_INCLUDED

#include <sge/audio/exception.hpp>
#include <sge/audio/file_exception_fwd.hpp>
#include <sge/media/declare_file_exception.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

SGE_MEDIA_DECLARE_FILE_EXCEPTION(sge::audio::exception);

FCPPT_PP_POP_WARNING

#endif
