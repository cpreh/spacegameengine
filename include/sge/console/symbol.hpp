#ifndef SGE_CONSOLE_SYMBOL_HPP_INCLUDED
#define SGE_CONSOLE_SYMBOL_HPP_INCLUDED

#ifdef sgeconsole_EXPORTS
#include <fcppt/export_symbol.hpp>
#define SGE_CONSOLE_SYMBOL FCPPT_EXPORT_SYMBOL
#else
#include <fcppt/import_symbol.hpp>
#define SGE_CONSOLE_SYMBOL FCPPT_IMPORT_SYMBOL
#endif

#endif
