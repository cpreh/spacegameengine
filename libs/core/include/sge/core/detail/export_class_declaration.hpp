//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CORE_DETAIL_EXPORT_CLASS_DECLARATION_HPP_INCLUDED
#define SGE_CORE_DETAIL_EXPORT_CLASS_DECLARATION_HPP_INCLUDED

#if defined(SGE_STATIC_LINK)
#define SGE_CORE_DETAIL_EXPORT_CLASS_DECLARATION
#else
#include <fcppt/symbol/export_class_instantiation.hpp>
#define SGE_CORE_DETAIL_EXPORT_CLASS_DECLARATION FCPPT_SYMBOL_EXPORT_CLASS_INSTANTIATION
#endif

#endif
