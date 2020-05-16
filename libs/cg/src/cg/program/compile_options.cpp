//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/char_type.hpp>
#include <sge/cg/string.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::cg::program::compile_options::compile_options()
:
	value_()
{
}

sge::cg::program::compile_options::compile_options(
	sge::cg::char_type const **_pointers
)
:
	value_()
{
	// TODO(philipp): Refactor this
	for(
		;
		*_pointers != nullptr;
		++_pointers // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
	)
	{
		value_.push_back(
			sge::cg::string(
				*_pointers
			)
		);
	}
}

sge::cg::program::compile_options::compile_options(
	string_sequence _value
)
:
	value_(
		std::move(
			_value
		)
	)
{
}

sge::cg::program::compile_options::pointer_sequence
sge::cg::program::compile_options::pointers() const
{
	sge::cg::program::compile_options::pointer_sequence result{
		fcppt::algorithm::map<
			sge::cg::program::compile_options::pointer_sequence
		>(
			value_,
			[](
				sge::cg::string const &_string
			)
			{
				return
					_string.c_str();
			}
		)
	};

	result.push_back(
		nullptr
	);

	return
		result;
}

sge::cg::program::compile_options::string_sequence const &
sge::cg::program::compile_options::value() const
{
	return
		value_;
}
