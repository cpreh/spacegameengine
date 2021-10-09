//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/resource_tree/path.hpp>
#include <sge/resource_tree/detail/strip_file_extension.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <iterator>
#include <numeric>
#include <fcppt/config/external_end.hpp>

sge::resource_tree::path
sge::resource_tree::detail::strip_file_extension(sge::resource_tree::path const &p)
{
  fcppt::string const &filename{p.back()};

  fcppt::string::size_type const dot_position = filename.find(FCPPT_TEXT('.'));

  if (dot_position == fcppt::string::npos)
  {
    return p;
  }

  return std::accumulate(
             p.begin(),
             std::prev(p.end()),
             sge::resource_tree::path(),
             [](sge::resource_tree::path const &_path, fcppt::string const &_element)
             { return _path / _element; }) /
         filename.substr(0, dot_position);
}
