//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RESOURCE_TREE_DETAIL_ELEMENT_DECL_HPP_INCLUDED
#define SGE_RESOURCE_TREE_DETAIL_ELEMENT_DECL_HPP_INCLUDED

#include <sge/resource_tree/path.hpp>
#include <sge/resource_tree/detail/element_fwd.hpp> // IWYU pragma: keep
#include <sge/resource_tree/detail/path_with_resource_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference_fwd.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/random/variate_decl.hpp>
#include <fcppt/random/wrapper/uniform_container_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge::resource_tree::detail
{
/**
\brief Represents one directory with the immediately contained resources (no recursion)

An element is a container for resources along with their paths. When the tree
is asked to return a resource (designated by a path, of course), it...

<ul>
	<li>
		...iterates through its elements and checks if the current
		element's base path is equal to the specified path or not.
	</li>
	<li>
		If it's equal, it calls sge::resource_tree::element::get_random to
		get a random element.
	</li>
	<li>
		If it's not equal, check if the element contains the path using
		sge::resource_tree::element::contains. If it doesn't,
		proceed to the next element. If it does contain the path,
		return the resource attached to it using
		sge::resource_tree::element::get.
	</li>
</ul>
*/
template <typename T, typename Rng>
class element
{
  FCPPT_NONCOPYABLE(element);

public:
  using resource_container = std::vector<sge::resource_tree::detail::path_with_resource<T>>;

  element(sge::resource_tree::path &&, resource_container &&, fcppt::reference<Rng>);

  element(element &&) noexcept;

  element &operator=(element &&) noexcept;

  ~element();

  [[nodiscard]] sge::resource_tree::path const &base_path() const;

  [[nodiscard]] T const &get_random() const;

  using optional_type = fcppt::optional::reference<T const>;

  [[nodiscard]] optional_type get_opt(sge::resource_tree::path const &) const;

private:
  sge::resource_tree::path base_path_;

  resource_container resources_;

  using container_distribution = fcppt::random::wrapper::uniform_container<resource_container>;

  using variate = fcppt::random::variate<Rng, container_distribution>;

  mutable fcppt::optional::object<variate> rng_;
};

}

#endif
