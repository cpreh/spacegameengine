//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/model/md3/exception.hpp>
#include <sge/model/md3/string.hpp>
#include <sge/model/md3/impl/max_qpath.hpp> // NOLINT(misc-include-cleaner)
#include <sge/model/md3/impl/read_string.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/find_opt.hpp>
#include <fcppt/array/object_impl.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <ios>
#include <istream>
#include <fcppt/config/external_end.hpp>

template <sge::model::md3::string::size_type Max>
sge::model::md3::string sge::model::md3::impl::read_string(std::istream &_stream)
{
  using char_type = sge::model::md3::string::value_type;

  using tmp_array = fcppt::array::object<char_type, Max>;

  tmp_array tmp_name{fcppt::no_init{}};

  if (!_stream.read(
          fcppt::cast::to_char_ptr<char *>(tmp_name.data()),
          fcppt::cast::size<std::streamsize>(fcppt::cast::to_signed(tmp_name.size()))))
  {
    throw sge::model::md3::exception(FCPPT_TEXT("Reading a string failed"));
  }

  return sge::model::md3::string(
      tmp_name.begin(),
      fcppt::optional::to_exception(
          fcppt::algorithm::find_opt(tmp_name, fcppt::literal<char_type>(0)),
          []
          {
            return sge::model::md3::exception(FCPPT_TEXT("String in md3 file not ended with a 0!"));
          }));
}

#define SGE_MODEL_MD3_INSTANTIATE_READ_STRING(maxc) \
  template sge::model::md3::string sge::model::md3::impl::read_string<maxc>(std::istream &)

SGE_MODEL_MD3_INSTANTIATE_READ_STRING(sge::model::md3::impl::max_qpath::value);

SGE_MODEL_MD3_INSTANTIATE_READ_STRING(16);
