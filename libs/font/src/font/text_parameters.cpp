//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/flags_field.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/align_h/variant.hpp>


sge::font::text_parameters::text_parameters(
	sge::font::align_h::variant const &_align_h
)
:
	align_h_(
		_align_h
	),
	flags_(
		sge::font::flags_field::null()
	)
{
}

sge::font::text_parameters &
sge::font::text_parameters::flags(
	sge::font::flags_field const &_flags
)
{
	flags_ = _flags;

	return
		*this;
}

sge::font::align_h::variant const &
sge::font::text_parameters::align_h() const
{
	return
		align_h_;
}

sge::font::flags_field const &
sge::font::text_parameters::flags() const
{
	return
		flags_;
}
