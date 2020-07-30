//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CONSOLE_MUXING_WIDE_STREAMBUF_HPP_INCLUDED
#define SGE_CONSOLE_MUXING_WIDE_STREAMBUF_HPP_INCLUDED

#include <sge/console/declare_muxing_streambuf.hpp>
#include <sge/console/muxing_streambuf.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sge
{
namespace console
{

using
muxing_wide_streambuf
=
sge::console::muxing_streambuf<
	wchar_t
>;

}
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

SGE_CONSOLE_DECLARE_MUXING_STREAMBUF(
	wchar_t
);

FCPPT_PP_POP_WARNING

#endif
