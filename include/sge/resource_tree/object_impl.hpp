/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_RESOURCE_TREE_OBJECT_IMPL_HPP_INCLUDED
#define SGE_RESOURCE_TREE_OBJECT_IMPL_HPP_INCLUDED

#include <sge/resource_tree/exception.hpp>
#include <sge/resource_tree/object_decl.hpp>
#include <sge/resource_tree/path.hpp>
#include <sge/resource_tree/detail/element_impl.hpp>
#include <sge/resource_tree/detail/init.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/find_by_opt.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename T,
	typename Rng
>
sge::resource_tree::object<
	T,
	Rng
>::object(
	boost::filesystem::path const &_path,
	path_to_resource_function const &_path_to_resource,
	rng_type &_random_generator
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

template<
	typename T,
	typename Rng
>
sge::resource_tree::object<
	T,
	Rng
>::~object()
{
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
								_elem.get_random()
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
		);
}

#endif
