//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE2D_CREATE_EXN_HPP_INCLUDED
#define SGE_IMAGE2D_CREATE_EXN_HPP_INCLUDED

#include <sge/image2d/file_unique_ptr.hpp>
#include <sge/image2d/system_ref.hpp>
#include <sge/image2d/detail/symbol.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/media/extension_fwd.hpp>

namespace sge::image2d
{

SGE_IMAGE2D_DETAIL_SYMBOL
sge::image2d::file_unique_ptr create_exn(
    sge::image2d::system_ref,
    sge::image2d::view::const_object const &,
    sge::media::extension const &);

}

#endif
