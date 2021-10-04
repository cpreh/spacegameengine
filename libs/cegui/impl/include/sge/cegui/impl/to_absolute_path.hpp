//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_IMPL_TO_ABSOLUTE_PATH_HPP_INCLUDED
#define SGE_CEGUI_IMPL_TO_ABSOLUTE_PATH_HPP_INCLUDED

#include <sge/cegui/impl/prefix.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace CEGUI
{
class String;
}

namespace sge::cegui::impl
{

std::filesystem::path
to_absolute_path(
	sge::cegui::impl::prefix const &,
	CEGUI::String const &filename
);

}

#endif
