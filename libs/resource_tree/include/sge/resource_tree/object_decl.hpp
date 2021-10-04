//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RESOURCE_TREE_OBJECT_DECL_HPP_INCLUDED
#define SGE_RESOURCE_TREE_OBJECT_DECL_HPP_INCLUDED

#include <sge/resource_tree/path_fwd.hpp>
#include <sge/resource_tree/path_to_resource_function.hpp>
#include <sge/resource_tree/detail/element_decl.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge::resource_tree
{
/**
\brief Represents a hierarchy of (homogenous) resources

\tparam T A copyable, assignable resource type such as a
<code>shared_ptr</code> to a resource (a texture/sound/etc.)

\tparam Rng A random number generator (for example
fcppt::random::generator::min_std_rand)

\section resource_tree_introduction Introduction

Every game needs some resources from the outside to run, like textures, sounds
etc.. You can load these resources either on-demand (lazy) when they are
needed, or all at once. When you do which depends on the circumstances. If it's
a small game where loading all the resources into memory is feasible, you might
want to do that. If it's a game with lots of resources, you might want to
create some of those on-demand.

In sge, we load all resources at once, since we're expecting to fit all
into system and video memory. sge::resource_tree::object helps us with
that.

\section resource_tree_goals Goals

There are a few major goals we want to achieve with the resource tree:

<ol>
	<li>
		We should be able to <em>group</em> resources together. For
		example, all asteroid textures should form a group. So should
		all firing sounds.
	</li>
	<li>
		Groups should be able to contain other groups to form a
		<em>hierarchy</em>. For example, all enemies should form a
		group, containing groups for the individual enemies'
		components.
	</li>
	<li>
		Adding members to the tree (i.e. adding new resources) should
		be very easy. Ideally, adding a new file to a directory should
		be enough.
	</li>
	<li>
		It should be possible to pick a random member from a group.
		This allows us to, say, pick a random asteroid image from the
		set of all asteroid images.
	</li>
</ol>

\section resource_tree_usage Usage

To create a resource tree, just specify a base path (for example,
<code>media/textures</code>), a function taking a path and returning the
resource and a random number generator. The tree class will then scan the given
path for resource files and convert them into resources. After the
initialization, each created resource  will have a unique path identifying it.
The path will be the same as the corresponding file's path, but without the
extension, for example, the file

<pre>
media/textures/ships/enemy01/hull.png
</pre>

Will result in a path

<pre>
media/textures/ships/enemy01/hull
</pre>

This makes two things possible:

<ol>
	<li>
		Switch to an image with a different format (and extension) without
		touching any code (since the extension will be stripped, anyway)
	</li>
	<li>
		Switch from using a <em>single</em> resource file (for example,
		the hull image above) to using a random image from a
		<em>collection</em>. For example, if you have created three hull images,
		<code>hull01.png, hull02.jpg, hull03.png</code> and want the
		game to choose between one of those, you <em>don't have to
		change the code</em>. The sge::resource_tree::object::get
		will act accordingly.
	</li>
</ol>

Note that we're not using std::filesystem::path to denote a path in the tree,
but our own class, sge::resource_tree::path.

\section resource_tree_internals Internals

To store the resources, we could have chosen a recursive data structure such as
fcppt::container::tree::object. However, since our use-case is very simple, it
was decided to store the resources in a list of
sge::resource_tree::element objects. Continue to the documentation for
that class for more information about the internal structure of the tree.
*/
template<
	typename T,
	typename Rng
>
class object
{
	FCPPT_NONMOVABLE(
		object
	);
public:
	using
	value_type
	=
	T;

	using
	rng_type
	=
	Rng;

	using
	path_to_resource_function
	=
	sge::resource_tree::path_to_resource_function<
		value_type
	>;

	/**
	\brief Construct a new resource tree
	*/
	object(
		std::filesystem::path const &,
		path_to_resource_function const &,
		fcppt::reference<
			rng_type
		>
	);

	~object();

	/**
	\brief Retrieve a resource
	*/
	[[nodiscard]]
	value_type const &
	get(
		sge::resource_tree::path const &
	) const;
private:
	using
	element_type
	=
	sge::resource_tree::detail::element<
		T,
		Rng
	>;

	using
	element_sequence
	=
	std::vector<
		element_type
	>;

	element_sequence const elements_;
};

}

#endif
