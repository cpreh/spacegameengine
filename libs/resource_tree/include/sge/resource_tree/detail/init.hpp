//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RESOURCE_TREE_DETAIL_INIT_HPP_INCLUDED
#define SGE_RESOURCE_TREE_DETAIL_INIT_HPP_INCLUDED

#include <sge/resource_tree/exception.hpp>
#include <sge/resource_tree/path_to_resource_function.hpp>
#include <sge/resource_tree/detail/add_directory.hpp>
#include <sge/resource_tree/detail/base_path.hpp>
#include <sge/resource_tree/detail/element_vector.hpp>
#include <sge/resource_tree/detail/sub_path.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/assert/throw_message.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/range/adaptor/filtered.hpp>
#include <filesystem>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace resource_tree
{
namespace detail
{

template<
	typename T,
	typename Rng
>
sge::resource_tree::detail::element_vector<
	T,
	Rng
>
init(
	std::filesystem::path const &_path,
	sge::resource_tree::path_to_resource_function<
		T
	> const &_path_to_resource,
	Rng &_random_generator
)
{
	FCPPT_ASSERT_THROW_MESSAGE(
		std::filesystem::exists(
			_path
		),
		sge::resource_tree::exception,
		fcppt::filesystem::path_to_string(
			_path
		)
		+
		FCPPT_TEXT(" does not exist!")
	);

	FCPPT_ASSERT_THROW_MESSAGE(
		std::filesystem::is_directory(
			_path
		),
		sge::resource_tree::exception,
		fcppt::filesystem::path_to_string(
			_path.string()
		)
		+
		FCPPT_TEXT(" is not a directory!")
	);

	typedef
	std::vector<
		std::filesystem::path
	>
	path_vector;

	path_vector const directories(
		fcppt::container::join(
			path_vector{
				_path
			},
			boost::make_iterator_range(
				std::filesystem::recursive_directory_iterator(
					_path
				),
				std::filesystem::recursive_directory_iterator()
			)
			|
			boost::adaptors::filtered(
				[](
					std::filesystem::path const &_cur_path
				)
				{
					return
						std::filesystem::is_directory(
							_cur_path
						);
				}
			)
		)
	);

	return
		fcppt::algorithm::map<
			sge::resource_tree::detail::element_vector<
				T,
				Rng
			>
		>(
			directories,
			[
				&_path,
				&_path_to_resource,
				&_random_generator
			](
				std::filesystem::path const &_cur_path
			)
			{
				return
					sge::resource_tree::detail::add_directory(
						sge::resource_tree::detail::base_path(
							_path
						),
						sge::resource_tree::detail::sub_path(
							_cur_path
						),
						_path_to_resource,
						_random_generator
					);
			}
		);
}

}
}
}

#endif
