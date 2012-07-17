/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RESOURCE_TREE_ELEMENT_IMPL_HPP_INCLUDED
#define SGE_RESOURCE_TREE_ELEMENT_IMPL_HPP_INCLUDED

#include <sge/resource_tree/element_decl.hpp>
#include <sge/resource_tree/path.hpp>
#include <sge/resource_tree/path_with_resource.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/random/variate_impl.hpp>
#include <fcppt/random/distribution/uniform_int_impl.hpp>


template<
	typename T,
	typename Rng
>
sge::resource_tree::element<
	T,
	Rng
>::element(
	resource_tree::path const &_base_path,
	resource_container const &_resources,
	Rng &_rng)
:
	base_path_(
		_base_path),
	resources_(
		_resources),
	rng_(
		_rng,
		// TODO: Create something else for this!
		container_distribution(
			typename container_distribution::min(
				0u),
			// Empty resource containers are allowed.
			// In this case, rng_ should not be used.
			typename container_distribution::max(
				resources_.empty()
				?
					0u
				:
					resources_.size() - 1u)))
{
}

template<
	typename T,
	typename Rng
>
sge::resource_tree::path const &
sge::resource_tree::element<
	T,
	Rng
>::base_path() const
{
	return
		base_path_;
}

template<
	typename T,
	typename Rng
>
bool
sge::resource_tree::element<
	T,
	Rng
>::contains(
	resource_tree::path const &s) const
{
	for(
		typename resource_container::const_iterator it =
			resources_.begin();
		it != resources_.end();
		++it)
		if(base_path_ / it->path().string() == s)
			return true;
	return false;
}

template<
	typename T,
	typename Rng
>
T
sge::resource_tree::element<
	T,
	Rng
>::get(
	resource_tree::path const &s) const
{
	FCPPT_ASSERT_PRE(
		this->contains(
			s));

	for(
		typename resource_container::const_iterator it =
			resources_.begin();
		it != resources_.end();
		++it)
		if(base_path_ / it->path().string() == s)
			return it->resource();

	FCPPT_ASSERT_UNREACHABLE;
}

template<
	typename T,
	typename Rng
>
T
sge::resource_tree::element<
	T,
	Rng
>::get_random() const
{
	FCPPT_ASSERT_PRE(
		!resources_.empty());

	return
		resources_[
			rng_()].resource();
}

template<
	typename T,
	typename Rng
>
sge::resource_tree::element<
	T,
	Rng
>::~element()
{
}

#endif
