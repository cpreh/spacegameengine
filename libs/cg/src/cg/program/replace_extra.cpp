/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/cg/string.hpp>
#include <sge/cg/program/extra_index.hpp>
#include <sge/cg/program/replace_extra.hpp>
#include <sge/cg/program/replace_extra_callback.hpp>
#include <sge/cg/program/source.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/config/compiler.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/xpressive/basic_regex.hpp>
#include <boost/xpressive/regex_actions.hpp>
#include <boost/xpressive/regex_algorithms.hpp>
#include <boost/xpressive/regex_primitives.hpp>
#include <fcppt/config/external_end.hpp>


sge::cg::program::source
sge::cg::program::replace_extra(
	sge::cg::program::source const &_source,
	sge::cg::program::replace_extra_callback const &_callback
)
{
	boost::xpressive::sregex const regex(
		boost::xpressive::as_xpr('$')
		>>
		(
			boost::xpressive::s1
			=
			+boost::xpressive::_d
		)
		>>
		boost::xpressive::as_xpr('$')
	);

FCPPT_PP_PUSH_WARNING
#if !defined(FCPPT_CONFIG_CLANG_COMPILER)
FCPPT_PP_DISABLE_GCC_WARNING(-Wzero-as-null-pointer-constant)
#endif

	return
		sge::cg::program::source(
			boost::xpressive::regex_replace(
				_source.get(),
				regex,
				boost::xpressive::val(
					fcppt::function<
						sge::cg::string (
							sge::cg::program::extra_index::value_type
						)
					>{
						[
							&_callback
						](
							sge::cg::program::extra_index::value_type const _value
						)
						->
						sge::cg::string
						{
							return
								_callback(
									sge::cg::program::extra_index{
										_value
									}
								);
						}
					}
				)(
					boost::xpressive::as<
						sge::cg::program::extra_index::value_type
					>(
						boost::xpressive::s1
					)
				)
			)
		);

FCPPT_PP_POP_WARNING
}
