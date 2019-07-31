//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/resource_tree/path.hpp>
#include <sge/resource_tree/detail/base_path.hpp>
#include <sge/resource_tree/detail/strip_path_prefix.hpp>
#include <sge/resource_tree/detail/sub_path.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


sge::resource_tree::path
sge::resource_tree::detail::strip_path_prefix(
	sge::resource_tree::detail::base_path const &_base_path,
	sge::resource_tree::detail::sub_path const &_sub_path)
{
	sge::resource_tree::path result;
	for(
		boost::filesystem::path::const_iterator it =
			std::next(
				_sub_path.get().begin(),
				std::distance(
					_base_path.get().begin(),
					_base_path.get().end()));
		it != _sub_path.get().end();
		++it)
		result /=
			fcppt::filesystem::path_to_string(
				it->string());
	return
		result;
}
