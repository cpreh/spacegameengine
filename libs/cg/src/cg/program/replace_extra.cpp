//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cg/string.hpp>
#include <sge/cg/program/extra_index.hpp>
#include <sge/cg/program/replace_extra.hpp>
#include <sge/cg/program/replace_extra_callback.hpp>
#include <sge/cg/program/source.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/preprocessor/disable_gnu_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/xpressive/basic_regex.hpp> // NOLINT(misc-include-cleaner)
#include <boost/xpressive/regex_actions.hpp>
#include <boost/xpressive/regex_algorithms.hpp>
#include <boost/xpressive/regex_primitives.hpp>
#include <boost/xpressive/xpressive_fwd.hpp>
#include <fcppt/config/external_end.hpp>

sge::cg::program::source sge::cg::program::replace_extra(
    sge::cg::program::source const &_source,
    sge::cg::program::replace_extra_callback const &_callback)
{
  boost::xpressive::sregex const regex(
      boost::xpressive::as_xpr('$') >> (boost::xpressive::s1 = +boost::xpressive::_d) >>
      boost::xpressive::as_xpr('$'));

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GNU_GCC_WARNING(-Wzero-as-null-pointer-constant)

  return sge::cg::program::source(boost::xpressive::regex_replace(
      _source.get(),
      regex,
      boost::xpressive::val(
          fcppt::function<sge::cg::string(sge::cg::program::extra_index::value_type)>{
              [&_callback](sge::cg::program::extra_index::value_type const _value)
                  -> sge::cg::string { return _callback(sge::cg::program::extra_index{_value}); }})(
          boost::xpressive::as<sge::cg::program::extra_index::value_type>(boost::xpressive::s1))));

  FCPPT_PP_POP_WARNING
}
