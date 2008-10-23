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

#define SGE_INSTANTIATE_APPLY_OPERATION(img, op)\
template SGE_SYMBOL \
op::result_type \
boost::gil::apply_operation(\
	img,\
	op);

#define SGE_INSTANTIATE_IMAGE_VIEW(variant)\
SGE_INSTANTIATE_APPLY_OPERATION(\
	variant &,\
	boost::gil::detail::destructor_op)\
SGE_INSTANTIATE_APPLY_OPERATION(\
	variant const &,\
	boost::gil::detail::equal_to_fn<variant::base_t>)\
SGE_INSTANTIATE_APPLY_OPERATION(\
	variant const &,\
	boost::gil::detail::copy_construct_in_place_fn<variant::base_t>)\
SGE_INSTANTIATE_APPLY_OPERATION(\
	variant const &,\
	boost::gil::detail::any_type_get_num_channels)\
SGE_INSTANTIATE_APPLY_OPERATION(\
	variant const &,\
	boost::gil::detail::any_type_get_dimensions)

SGE_INSTANTIATE_IMAGE_VIEW(const_image_view_elements)
SGE_INSTANTIATE_IMAGE_VIEW(image_view_elements)

#undef SGE_INSTANTIATE_APPLY_OPERATION
#undef SGE_INSTANTIATE_IMAGE_VIEW
