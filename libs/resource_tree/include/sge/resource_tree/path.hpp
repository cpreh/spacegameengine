//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RESOURCE_TREE_PATH_HPP_INCLUDED
#define SGE_RESOURCE_TREE_PATH_HPP_INCLUDED

#include <sge/resource_tree/path_fwd.hpp>
#include <sge/resource_tree/detail/symbol.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge::resource_tree
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
  using element_sequence = std::vector<fcppt::string>;

public:
  using iterator = element_sequence::iterator;

  using const_iterator = element_sequence::const_iterator;

  SGE_RESOURCE_TREE_DETAIL_SYMBOL
  path();

  SGE_RESOURCE_TREE_DETAIL_SYMBOL
  path &operator/=(fcppt::string const &);

  [[nodiscard]] SGE_RESOURCE_TREE_DETAIL_SYMBOL path operator/(fcppt::string const &) const;

  [[nodiscard]] SGE_RESOURCE_TREE_DETAIL_SYMBOL const_iterator begin() const;

  [[nodiscard]] SGE_RESOURCE_TREE_DETAIL_SYMBOL const_iterator end() const;

  [[nodiscard]] SGE_RESOURCE_TREE_DETAIL_SYMBOL bool operator==(path const &) const;

  /**
	\brief Return the last element of the path
	*/
  [[nodiscard]] SGE_RESOURCE_TREE_DETAIL_SYMBOL fcppt::string const &back() const;

  /**
	\brief Output the path as a string for display in error messages
	*/
  [[nodiscard]] SGE_RESOURCE_TREE_DETAIL_SYMBOL fcppt::string string() const;

private:
  element_sequence elements_;
};

}

#endif
