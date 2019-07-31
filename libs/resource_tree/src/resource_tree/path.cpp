//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/resource_tree/path.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/join_strings.hpp>


sge::resource_tree::path::path()
:
	elements_()
{
}

sge::resource_tree::path &
sge::resource_tree::path::operator/=(
	fcppt::string const &_path
)
{
	elements_.push_back(
		_path
	);

	return
		*this;
}

sge::resource_tree::path
sge::resource_tree::path::operator/(
	fcppt::string const &_path
) const
{
	path result(
		*this
	);

	result /= _path;

	return
		result;
}

sge::resource_tree::path::const_iterator
sge::resource_tree::path::begin() const
{
	return
		elements_.begin();
}

sge::resource_tree::path::const_iterator
sge::resource_tree::path::end() const
{
	return
		elements_.end();
}

bool
sge::resource_tree::path::operator==(
	sge::resource_tree::path const &_other
) const
{
	return
		_other.elements_
		==
		elements_;
}

fcppt::string const &
sge::resource_tree::path::back() const
{
	return
		elements_.back();
}

fcppt::string
sge::resource_tree::path::string() const
{
	return
		fcppt::algorithm::join_strings(
			elements_,
			FCPPT_TEXT("/")
		);
}
