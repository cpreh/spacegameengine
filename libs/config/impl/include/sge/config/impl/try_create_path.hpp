//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CONFIG_IMPL_TRY_CREATE_PATH_HPP_INCLUDED
#define SGE_CONFIG_IMPL_TRY_CREATE_PATH_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace config
{
namespace impl
{

std::filesystem::path
try_create_path(
	std::filesystem::path const &
);

}
}
}

#endif
