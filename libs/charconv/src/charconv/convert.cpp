//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/charconv/char_type.hpp>
#include <sge/charconv/conversion_failed.hpp>
#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/charconv/string_type.hpp>
#include <sge/charconv/detail/pp_encodings.hpp>
#include <sge/core/impl/export_function_instantiation.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/locale/encoding_errors.hpp>
#include <boost/locale/encoding_utf.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <fcppt/config/external_end.hpp>

template <sge::charconv::encoding DestEncoding, sge::charconv::encoding SourceEncoding>
sge::charconv::string_type<DestEncoding>
sge::charconv::convert(sge::charconv::string_type<SourceEncoding> const &_source)
try
{
  return boost::locale::conv::utf_to_utf<sge::charconv::char_type<DestEncoding>>(
      _source, boost::locale::conv::stop);
}
catch (boost::locale::conv::conversion_error const &)
{
  throw sge::charconv::conversion_failed{};
}

#define SGE_CHARCONV_INSTANTIATE_ENCODING(r, param) \
  template SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION \
      sge::charconv::string_type<BOOST_PP_SEQ_ELEM(0, param)> \
      sge::charconv::convert<BOOST_PP_SEQ_ELEM(0, param), BOOST_PP_SEQ_ELEM(1, param)>( \
          sge::charconv::string_type<BOOST_PP_SEQ_ELEM(1, param)> const &);

BOOST_PP_SEQ_FOR_EACH_PRODUCT(
    SGE_CHARCONV_INSTANTIATE_ENCODING,
    (SGE_CHARCONV_DETAIL_PP_ENCODINGS)(SGE_CHARCONV_DETAIL_PP_ENCODINGS))
