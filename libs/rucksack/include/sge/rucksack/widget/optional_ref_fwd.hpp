//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RUCKSACK_WIDGET_OPTIONAL_REF_FWD_HPP_INCLUDED
#define SGE_RUCKSACK_WIDGET_OPTIONAL_REF_FWD_HPP_INCLUDED

#include <sge/rucksack/widget/base_fwd.hpp>
#include <fcppt/optional/reference_fwd.hpp>


namespace sge::rucksack::widget
{

using
optional_ref
=
fcppt::optional::reference<
	sge::rucksack::widget::base
>;

}

#endif
