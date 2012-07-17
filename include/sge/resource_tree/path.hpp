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


#ifndef SGE_RESOURCE_TREE_PATH_HPP_INCLUDED
#define SGE_RESOURCE_TREE_PATH_HPP_INCLUDED

#include <sge/resource_tree/path_fwd.hpp>
#include <sge/resource_tree/symbol.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace resource_tree
{
/**
\brief A glorified vector of strings used to locate a resource or group in the tree

The path class has just the operations to work with the tree, it's not a
general-purpose data structure. The user can construct paths "inline" using the
constructor, together with the <code>operator/</code>, like this:

\code
sge::resource_tree::path() / FCPPT_TEXT("foo") / FCPPT_TEXT("bar")
\endcode
*/
class path
{
private:
	typedef
	std::vector<fcppt::string>
	element_sequence;
public:
	typedef
	element_sequence::iterator
	iterator;

	typedef
	element_sequence::const_iterator
	const_iterator;

	SGE_RESOURCE_TREE_SYMBOL
	path();

	SGE_RESOURCE_TREE_SYMBOL
	path &
	operator/=(
		fcppt::string const &);

	SGE_RESOURCE_TREE_SYMBOL
	path
	operator/(
		fcppt::string const &) const;

	SGE_RESOURCE_TREE_SYMBOL
	const_iterator const
	begin() const;

	SGE_RESOURCE_TREE_SYMBOL
	const_iterator const
	end() const;

	SGE_RESOURCE_TREE_SYMBOL
	bool
	operator==(
		path const &) const;

	/**
	\brief Return the last element of the path
	*/
	SGE_RESOURCE_TREE_SYMBOL
	fcppt::string const
	back() const;

	/**
	\brief Output the path as a string for display in error messages
	*/
	SGE_RESOURCE_TREE_SYMBOL
	fcppt::string const
	string() const;
private:
	element_sequence elements_;
};
}
}

#endif
