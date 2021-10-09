//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/model/md3/exception.hpp>
#include <sge/model/md3/u8.hpp>
#include <sge/model/md3/impl/endian.hpp>
#include <sge/model/md3/impl/read_and_check_id3p.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/text.hpp>
#include <fcppt/array/object.hpp>
#include <fcppt/io/read.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <fcppt/config/external_end.hpp>

bool sge::model::md3::impl::read_and_check_id3p(std::istream &_stream)
{
  using id3p_array = fcppt::array::object<sge::model::md3::u8, 4>;

  id3p_array const to_check{
      fcppt::literal<sge::model::md3::u8>(0x49),
      fcppt::literal<sge::model::md3::u8>(0x44),
      fcppt::literal<sge::model::md3::u8>(0x50),
      fcppt::literal<sge::model::md3::u8>(0x33)};

  id3p_array id3p{fcppt::no_init{}};

  for (auto &elem : id3p)
  {
    elem = fcppt::optional::to_exception(
        fcppt::io::read<sge::model::md3::u8>(_stream, sge::model::md3::impl::endian()),
        [] { return sge::model::md3::exception{FCPPT_TEXT("Failed reading id3p")}; });
  }

  return to_check == id3p;
}
