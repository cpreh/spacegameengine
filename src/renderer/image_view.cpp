/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/image_view.hpp>
#include <sge/renderer/image_view_impl.hpp>
#include <sge/export.hpp>

typedef boost::gil::variant<
	boost::gil::detail::views_get_const_t<
		sge::renderer::image_view_elements
	>::type
> const_image_view_elements;

typedef boost::gil::variant<
	sge::renderer::image_view_elements
> image_view_elements;

template SGE_SYMBOL
boost::gil::detail::destructor_op::result_type
boost::gil::apply_operation(
	const_image_view_elements &,
	boost::gil::detail::destructor_op);

template SGE_SYMBOL
boost::gil::detail::equal_to_fn<const_image_view_elements::base_t>::result_type
boost::gil::apply_operation(
	const_image_view_elements const &,
	boost::gil::detail::equal_to_fn<const_image_view_elements::base_t>);

template SGE_SYMBOL
boost::gil::detail::copy_construct_in_place_fn<const_image_view_elements::base_t>::result_type
boost::gil::apply_operation(
	const_image_view_elements const &,
	boost::gil::detail::copy_construct_in_place_fn<const_image_view_elements::base_t>);

template SGE_SYMBOL
boost::gil::detail::any_type_get_num_channels::result_type
boost::gil::apply_operation(
	const_image_view_elements const &,
	boost::gil::detail::any_type_get_num_channels);

template SGE_SYMBOL
boost::gil::detail::any_type_get_dimensions::result_type
boost::gil::apply_operation(
	const_image_view_elements const &,
	boost::gil::detail::any_type_get_dimensions);




template SGE_SYMBOL
boost::gil::detail::destructor_op::result_type
boost::gil::apply_operation(
	image_view_elements &,
	boost::gil::detail::destructor_op);

template SGE_SYMBOL
boost::gil::detail::equal_to_fn<image_view_elements::base_t>::result_type
boost::gil::apply_operation(
	image_view_elements const &,
	boost::gil::detail::equal_to_fn<image_view_elements::base_t>);

template SGE_SYMBOL
boost::gil::detail::copy_construct_in_place_fn<image_view_elements::base_t>::result_type
boost::gil::apply_operation(
	image_view_elements const &,
	boost::gil::detail::copy_construct_in_place_fn<image_view_elements::base_t>);

template SGE_SYMBOL
boost::gil::detail::any_type_get_num_channels::result_type
boost::gil::apply_operation(
	image_view_elements const &,
	boost::gil::detail::any_type_get_num_channels);

template SGE_SYMBOL
boost::gil::detail::any_type_get_dimensions::result_type
boost::gil::apply_operation(
	image_view_elements const &,
	boost::gil::detail::any_type_get_dimensions);
