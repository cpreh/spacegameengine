//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_INI_TYPED_RESULT_TYPE_HPP_INCLUDED
#define SGE_PARSE_INI_TYPED_RESULT_TYPE_HPP_INCLUDED

#include <fcppt/deref_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::parse::ini::typed
{
template <typename Parser>
using result_type = std::remove_cvref_t<fcppt::deref_type<Parser>>::result_type;
}

#endif
