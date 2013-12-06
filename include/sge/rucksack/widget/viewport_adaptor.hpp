/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RUCKSACK_WIDGET_VIEWPORT_ADAPTOR_HPP_INCLUDED
#define SGE_RUCKSACK_WIDGET_VIEWPORT_ADAPTOR_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <sge/rucksack/axis_policy2_fwd.hpp>
#include <sge/rucksack/dim_fwd.hpp>
#include <sge/rucksack/symbol.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sge
{
namespace rucksack
{
namespace widget
{
/**
 * The viewport adaptor has just one single child. It synchronizes the size and
 * position of this child with the given viewport. So in a hierarchy, this
 * manager is supposed to be near the top.
 *
 * The operations size(...) and position(...) resize and reposition the
 * viewport.
 *
 * Note that you _can_ use this class with a parent (in which case the viewport
 * will be changed by the parent) but I don't know any use case for this, since
 * a renderer can only have one viewport at a time.
 */
class SGE_CLASS_SYMBOL viewport_adaptor
:
	public sge::rucksack::widget::base
{
FCPPT_NONCOPYABLE(
	viewport_adaptor);
public:
	// We need the renderer object for the size() and position() getters/setters.
	// The viewport manager ironically doesn't give us access to the viewport
	// directly.
	SGE_RUCKSACK_SYMBOL explicit
	viewport_adaptor(
		sge::viewport::manager &,
		sge::renderer::device::core &);

	SGE_RUCKSACK_SYMBOL void
	size(
		sge::rucksack::dim const &);

	SGE_RUCKSACK_SYMBOL void
	position(
		sge::rucksack::vector const &);

	SGE_RUCKSACK_SYMBOL sge::rucksack::dim const
	size() const;

	SGE_RUCKSACK_SYMBOL sge::rucksack::vector const
	position() const;

	SGE_RUCKSACK_SYMBOL sge::rucksack::axis_policy2 const
	axis_policy() const;

	SGE_RUCKSACK_SYMBOL void
	relayout();

	SGE_RUCKSACK_SYMBOL void
	child(
		sge::rucksack::widget::base &);

	SGE_RUCKSACK_SYMBOL ~viewport_adaptor();
private:
	sge::renderer::target::base &target_;

	sge::rucksack::widget::base *child_;

	fcppt::signal::scoped_connection const viewport_connection_;

	void
	manage_callback();

	void
	child_destroyed(
		sge::rucksack::widget::base &);
};
}
}
}

#endif
