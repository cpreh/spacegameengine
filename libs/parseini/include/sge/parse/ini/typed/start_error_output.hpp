//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_INI_TYPED_START_ERROR_OUTPUT_HPP_INCLUDED
#define SGE_PARSE_INI_TYPED_START_ERROR_OUTPUT_HPP_INCLUDED

#include <sge/parse/ini/detail/symbol.hpp>
#include <sge/parse/ini/typed/start_error_fwd.hpp>
#include <fcppt/io/ostream_fwd.hpp>

namespace sge::parse::ini::typed
{

SGE_PARSE_INI_DETAIL_SYMBOL
fcppt::io::ostream &operator<<(fcppt::io::ostream &, sge::parse::ini::typed::start_error const &);

}

#endif
