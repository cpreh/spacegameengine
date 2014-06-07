/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <fcppt/config/external_begin.hpp>
#include <boost/xpressive/basic_regex.hpp>
#include <boost/xpressive/regex_actions.hpp>
#include <boost/xpressive/regex_algorithms.hpp>
#include <boost/xpressive/regex_primitives.hpp>
#include <fcppt/config/external_end.hpp>


namespace
{

class replace_functor
{
	FCPPT_NONASSIGNABLE(
		replace_functor
	);
public:
	explicit
	replace_functor(
		sge::cg::program::replace_extra_callback const &
	);

	typedef sge::cg::string result_type;

	result_type
	operator()(
		sge::cg::program::extra_index::value_type
	) const;
private:
	sge::cg::program::replace_extra_callback const callback_;
};

}

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

	return
		sge::cg::program::source(
			boost::xpressive::regex_replace(
				_source.get(),
				regex,
				boost::xpressive::val(
					replace_functor(
						_callback
					)
				)(
					boost::xpressive::as<
						sge::cg::program::extra_index::value_type
					>(
						boost::xpressive::s1
					)
				)
			)
		);
}

namespace
{

replace_functor::replace_functor(
	sge::cg::program::replace_extra_callback const &_callback
)
:
	callback_(
		_callback
	)
{
}

replace_functor::result_type
replace_functor::operator()(
	sge::cg::program::extra_index::value_type const _value
) const
{
	return
		callback_(
			sge::cg::program::extra_index(
				_value
			)
		);
}

}
