//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GDIFONT_CREATE_DIB_SECTION_HPP_INCLUDED
#define SGE_GDIFONT_CREATE_DIB_SECTION_HPP_INCLUDED

#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/hbitmap_unique_ptr.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/image2d/dim_fwd.hpp>

namespace sge
{
namespace gdifont
{

sge::gdifont::hbitmap_unique_ptr create_dib_section(
    sge::gdifont::device_context const &, sge::image2d::dim const &, VOID *&bits_result);

}
}

#endif
