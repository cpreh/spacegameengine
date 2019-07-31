//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CHARCONV_IMPL_FCPPT_IS_UTF8_HPP_INCLUDED
#define SGE_CHARCONV_IMPL_FCPPT_IS_UTF8_HPP_INCLUDED

#include <fcppt/public_config.hpp>
#include <fcppt/config/platform.hpp>


#if defined(FCPPT_CONFIG_POSIX_PLATFORM) && defined(FCPPT_NARROW_STRING)
#define SGE_CHARCONV_IMPL_FCPPT_IS_UTF8
#endif

#endif
