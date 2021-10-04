//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CONFIG_MEDIA_PATH_HPP_INCLUDED
#define SGE_CONFIG_MEDIA_PATH_HPP_INCLUDED

#include <sge/config/detail/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sge::config
{

SGE_CONFIG_DETAIL_SYMBOL
std::filesystem::path
media_path();

}

#endif
