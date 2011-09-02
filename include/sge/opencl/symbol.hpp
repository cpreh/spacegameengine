#ifndef SGE_OPENCL_SYMBOL_HPP_INCLUDED
#define SGE_OPENCL_SYMBOL_HPP_INCLUDED

#ifdef sgeopencl_EXPORTS
#include <fcppt/export_symbol.hpp>
#define SGE_OPENCL_SYMBOL FCPPT_EXPORT_SYMBOL
#else
#include <fcppt/import_symbol.hpp>
#define SGE_OPENCL_SYMBOL FCPPT_IMPORT_SYMBOL
#endif

#endif
