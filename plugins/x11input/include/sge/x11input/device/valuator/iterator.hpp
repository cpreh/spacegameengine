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


#ifndef SGE_X11INPUT_DEVICE_VALUATOR_ITERATOR_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_VALUATOR_ITERATOR_HPP_INCLUDED

#include <sge/x11input/device/valuator/index.hpp>
#include <sge/x11input/device/valuator/iterator_base.hpp>
#include <sge/x11input/device/valuator/iterator_fwd.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <boost/iterator/iterator_facade.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace device
{
namespace valuator
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

class iterator
:
	public sge::x11input::device::valuator::iterator_base
{
public:
	iterator(
		sge::x11input::device::valuator::index,
		XIValuatorState const &
	);
private:
	friend class boost::iterator_core_access;

	void
	increment();

	bool
	equal(
		iterator const &
	) const;

	reference
	dereference() const;

	void
	index_to_next_valuator();

	fcppt::reference<
		XIValuatorState const
	> state_;

	double const *valuator_;

	sge::x11input::device::valuator::index index_;

	sge::x11input::device::valuator::index length_;
};

FCPPT_PP_POP_WARNING

}
}
}
}

#endif
