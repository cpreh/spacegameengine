//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CONSOLE_DECLARE_MUXING_STREAMBUF_HPP_INCLUDED
#define SGE_CONSOLE_DECLARE_MUXING_STREAMBUF_HPP_INCLUDED

#include <sge/console/muxing_streambuf.hpp> // IWYU pragma: keep
#include <sge/core/detail/export_class_declaration.hpp>

#define SGE_CONSOLE_DECLARE_MUXING_STREAMBUF(char_type) \
  extern template class SGE_CORE_DETAIL_EXPORT_CLASS_DECLARATION \
      sge::console::muxing_streambuf<char_type>

#endif
