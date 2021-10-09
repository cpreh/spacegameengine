//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE2D_LOAD_HPP_INCLUDED
#define SGE_IMAGE2D_LOAD_HPP_INCLUDED

#include <sge/image2d/optional_file_unique_ptr.hpp>
#include <sge/image2d/system_ref.hpp>
#include <sge/image2d/detail/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

namespace sge::image2d
{

SGE_IMAGE2D_DETAIL_SYMBOL
sge::image2d::optional_file_unique_ptr
load(sge::image2d::system_ref, std::filesystem::path const &);

}

#endif
