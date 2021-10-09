//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CORE_CHECK_STATE_HPP_INCLUDED
#define SGE_CORE_CHECK_STATE_HPP_INCLUDED

#include <fcppt/format.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/preprocessor/file.hpp>
#include <fcppt/preprocessor/stringize.hpp>

#define SGE_CORE_CHECK_STATE( \
    exception, message, error_type, function, success_code, error_code_function) \
  { \
    error_type const sge_return_value_(function); \
\
    if (sge_return_value_ != success_code) \
      throw exception( \
          (fcppt::format(FCPPT_TEXT("Function failed in %1%:%2% (errorcode: %3%): %4%")) % \
           FCPPT_PP_FILE % FCPPT_PP_STRINGIZE(__LINE__) % error_code_function(sge_return_value_) % \
           (message)) \
              .str()); \
  }

#endif
