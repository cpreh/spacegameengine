//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SHADER_ISTREAM_REF_HPP_INCLUDED
#define SGE_SHADER_ISTREAM_REF_HPP_INCLUDED

#include <fcppt/reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace sge::shader
{

using istream_ref = fcppt::reference<std::istream>;

}

#endif
