//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_SCHEME_FILE_HPP_INCLUDED
#define SGE_CEGUI_SCHEME_FILE_HPP_INCLUDED

#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sge::cegui
{

FCPPT_DECLARE_STRONG_TYPEDEF(
	std::filesystem::path,
	scheme_file
);

}

#endif
