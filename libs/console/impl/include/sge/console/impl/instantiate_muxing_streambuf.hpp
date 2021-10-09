//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CONSOLE_IMPL_INSTANTIATE_MUXING_STREAMBUF_HPP_INCLUDED
#define SGE_CONSOLE_IMPL_INSTANTIATE_MUXING_STREAMBUF_HPP_INCLUDED

#include <sge/console/impl/muxing_streambuf_impl.hpp>
#include <sge/core/impl/export_class_instantiation.hpp>

#define SGE_CONSOLE_IMPL_INSTANTIATE_MUXING_STREAMBUF(char_type) \
  template class SGE_CORE_IMPL_EXPORT_CLASS_INSTANTIATION sge::console::muxing_streambuf<char_type>

#endif
