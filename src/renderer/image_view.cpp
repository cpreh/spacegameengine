#include <sge/renderer/image_view.hpp>
#include <sge/renderer/image_view_impl.hpp>

typedef boost::gil::variant<
	boost::gil::detail::views_get_const_t<
		sge::renderer::image_view_elements
	>::type
> const_image_view_elements;

typedef boost::gil::variant<
	sge::renderer::image_view_elements
> image_view_elements;

template
boost::gil::detail::destructor_op::result_type
boost::gil::apply_operation(
	const_image_view_elements &,
	boost::gil::detail::destructor_op);

template
boost::gil::detail::equal_to_fn<const_image_view_elements::base_t>::result_type
boost::gil::apply_operation(
	const_image_view_elements &,
	boost::gil::detail::equal_to_fn<const_image_view_elements::base_t>);

template
boost::gil::detail::copy_construct_in_place_fn<const_image_view_elements::base_t>::result_type
boost::gil::apply_operation(
	const_image_view_elements &,
	boost::gil::detail::copy_construct_in_place_fn<const_image_view_elements::base_t>);

template
boost::gil::detail::any_type_get_num_channels::result_type
boost::gil::apply_operation(
	const_image_view_elements &,
	boost::gil::detail::any_type_get_num_channels);

template
boost::gil::detail::any_type_get_dimensions::result_type
boost::gil::apply_operation(
	const_image_view_elements &,
	boost::gil::detail::any_type_get_dimensions);




template
boost::gil::detail::destructor_op::result_type
boost::gil::apply_operation(
	image_view_elements &,
	boost::gil::detail::destructor_op);

template
boost::gil::detail::equal_to_fn<image_view_elements::base_t>::result_type
boost::gil::apply_operation(
	image_view_elements &,
	boost::gil::detail::equal_to_fn<image_view_elements::base_t>);

template
boost::gil::detail::copy_construct_in_place_fn<image_view_elements::base_t>::result_type
boost::gil::apply_operation(
	image_view_elements &,
	boost::gil::detail::copy_construct_in_place_fn<image_view_elements::base_t>);

template
boost::gil::detail::any_type_get_num_channels::result_type
boost::gil::apply_operation(
	image_view_elements &,
	boost::gil::detail::any_type_get_num_channels);

template
boost::gil::detail::any_type_get_dimensions::result_type
boost::gil::apply_operation(
	image_view_elements &,
	boost::gil::detail::any_type_get_dimensions);
