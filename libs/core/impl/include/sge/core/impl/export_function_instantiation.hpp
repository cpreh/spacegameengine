//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION_HPP_INCLUDED
#define SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION_HPP_INCLUDED

#ifdef SGE_STATIC_LINK
#define SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION
#else
#include <fcppt/symbol/export_function_instantiation.hpp>
#define SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION FCPPT_SYMBOL_EXPORT_FUNCTION_INSTANTIATION
#endif

#endif
