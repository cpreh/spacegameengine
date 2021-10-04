//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE2D_SAVE_FROM_VIEW_HPP_INCLUDED
#define SGE_IMAGE2D_SAVE_FROM_VIEW_HPP_INCLUDED

#include <sge/image2d/system_fwd.hpp>
#include <sge/image2d/detail/symbol.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sge::image2d
{

SGE_IMAGE2D_DETAIL_SYMBOL
void
save_from_view(
	sge::image2d::system &, // NOLINT(google-runtime-references)
	sge::image2d::view::const_object const &,
	std::filesystem::path const &
);

}

#endif
