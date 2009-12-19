/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_GUI_LAYOUTS_ROW_HPP_INCLUDED
#define SGE_GUI_LAYOUTS_ROW_HPP_INCLUDED

#include <sge/gui/layouts/base.hpp>
#include <sge/gui/widgets/fwd.hpp>
#include <sge/gui/export.hpp>
#include <sge/gui/size_policy.hpp>
#include <fcppt/math/dim/basic_decl.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <vector>
#include <cstddef>

namespace sge
{
namespace gui
{
namespace layouts
{
class SGE_CLASS_SYMBOL row : public base
{
	public:
	typedef fcppt::math::vector::static_<float,2>::type spacing;

	SGE_GUI_SYMBOL row(
		spacing const & =
			spacing(
				static_cast<spacing::value_type>(1.1),
				static_cast<spacing::value_type>(1.1)));
	SGE_GUI_SYMBOL void compile_static();
	SGE_GUI_SYMBOL void pos(point const &);
	SGE_GUI_SYMBOL void size(dim const &);
	SGE_GUI_SYMBOL dim const optimal_size() const;
	private:
	virtual dim::reference master(
		dim &) const = 0;
	virtual dim::const_reference master(
		dim const &) const = 0;
	virtual point::reference master(
		point &) const = 0;
	virtual point::const_reference master(
		point const &) const = 0;
	dim::reference slave(
		dim &) const;
	dim::const_reference slave(
		dim const &) const;
	point::reference slave(
		point &) const;
	point::const_reference slave(
		point const &) const;

	void adapt(
		dim const &,
		dim const &,
		axis_policy::type,
		dim::size_type);
	void adapt_outer(
		dim const &,
		dim const &,
		dim::size_type);
	void update_widgets(
		dim const &);
	void reset_cache();
	unsigned count_flags(
		axis_policy::type,
		dim::size_type) const;
	void do_compile(
		dim const &);

	typedef std::vector<
		std::pair<
			widgets::base*,
			dim>
			> widget_map;

	widget_map sizes;
	spacing spacing_;
};
}
}
}

#endif
