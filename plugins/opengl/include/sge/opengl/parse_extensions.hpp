//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_PARSE_EXTENSIONS_HPP_INCLUDED
#define SGE_OPENGL_PARSE_EXTENSIONS_HPP_INCLUDED

#include <sge/opengl/extension_set.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/iterator/make_range.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <sstream>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace sge::opengl
{

template <typename Type>
sge::opengl::extension_set<Type> parse_extensions(std::string const &_extensions)
{
  std::istringstream stream(_extensions);

  using iterator = std::istream_iterator<std::string>;

  return fcppt::algorithm::map<sge::opengl::extension_set<Type>>(
      fcppt::iterator::make_range(iterator(stream), iterator()),
      [](std::string const &_element) { return Type(_element); });
}

}

#endif
