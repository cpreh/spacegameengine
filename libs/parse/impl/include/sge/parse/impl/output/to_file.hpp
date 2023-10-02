//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PARSE_IMPL_OUTPUT_TO_FILE_HPP_INCLUDED
#define SGE_PARSE_IMPL_OUTPUT_TO_FILE_HPP_INCLUDED

#include <sge/parse/exception.hpp>
#include <fcppt/filesystem/open_exn.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fstream>
#include <ios>
#include <fcppt/config/external_end.hpp>

namespace sge::parse::impl::output
{

template <typename Ch, typename ToStream, typename Data>
[[nodiscard]] bool
to_file(ToStream const &_to_stream, std::filesystem::path const &_path, Data const &_data)
{
  // TODO(philipp): Should we return false instead of throwing an exception?
  // NOLINTNEXTLINE(misc-const-correctness)
  std::basic_ofstream<Ch> ofs{
      fcppt::filesystem::open_exn<std::basic_ofstream<Ch>, sge::parse::exception>(
          _path, std::ios_base::binary)};

  _to_stream(ofs, _data);

  return ofs.good();
}
}

#endif
