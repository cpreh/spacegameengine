//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RESOURCE_TREE_OBJECT_IMPL_HPP_INCLUDED
#define SGE_RESOURCE_TREE_OBJECT_IMPL_HPP_INCLUDED

#include <sge/resource_tree/exception.hpp>
#include <sge/resource_tree/object_decl.hpp>
#include <sge/resource_tree/path.hpp>
#include <sge/resource_tree/detail/element_impl.hpp>
#include <sge/resource_tree/detail/init.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/find_by_opt.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


template<
	typename T,
	typename Rng
>
sge::resource_tree::object<
	T,
	Rng
>::object(
	std::filesystem::path const &_path,
	path_to_resource_function const &_path_to_resource,
	fcppt::reference<
		rng_type
	> const _random_generator
)
:
	elements_(
		sge::resource_tree::detail::init(
			_path,
			_path_to_resource,
			_random_generator
		)
	)
{
}

namespace sge::resource_tree
{
template<
	typename T,
	typename Rng
>
object<
	T,
	Rng
>::~object()
= default;
}

template<
	typename T,
	typename Rng
>
typename
sge::resource_tree::object<
	T,
	Rng
>::value_type const &
sge::resource_tree::object<
	T,
	Rng
>::get(
	sge::resource_tree::path const &_path
) const
{
	// Two choices: Either the specified path is a _file_ or a _directory_.
	//
	// If it's a _directory_, we can find it directly. It'll be the
	// base_path member of the element.
	//
	// If it's a _file_, it will be contained inside an element with the
	// according prefix.
	return
		fcppt::optional::to_exception(
			fcppt::algorithm::find_by_opt(
				elements_,
				[
					&_path
				](
					element_type const &_elem
				)
				{
					return
						_elem.base_path()
						==
						_path
						?
							typename
							element_type::optional_type{
								fcppt::make_cref(
									_elem.get_random()
								)
							}
						:
							_elem.get_opt(
								_path
							)
						;
				}
			),
			[
				&_path
			]{
				return
					sge::resource_tree::exception(
						FCPPT_TEXT("Tried to access the location \"")
						+
						_path.string()
						+
						FCPPT_TEXT("\" which could not be found in the resource tree.")
					);
			}
		).get();
}

#endif
