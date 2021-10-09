//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_LIBPNG_OPTIONAL_FILE_REP_FWD_HPP_INCLUDED
#define SGE_LIBPNG_OPTIONAL_FILE_REP_FWD_HPP_INCLUDED

#include <sge/libpng/file_rep_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>

namespace sge::libpng
{

using optional_file_rep = fcppt::optional::object<sge::libpng::file_rep>;

}

#endif
