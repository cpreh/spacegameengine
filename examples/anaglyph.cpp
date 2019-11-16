//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/camera/perspective_projection_from_viewport.hpp>
#include <sge/camera/projection_matrix.hpp>
#include <sge/camera/update_duration.hpp>
#include <sge/camera/coordinate_system/forward.hpp>
#include <sge/camera/coordinate_system/identity.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/coordinate_system/position.hpp>
#include <sge/camera/coordinate_system/right.hpp>
#include <sge/camera/first_person/movement_speed.hpp>
#include <sge/camera/first_person/object.hpp>
#include <sge/camera/first_person/parameters.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/config/media_path.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/input/event_base.hpp>
#include <sge/log/location.hpp>
#include <sge/log/option.hpp>
#include <sge/log/option_container.hpp>
#include <sge/model/md3/create.hpp>
#include <sge/model/md3/index_sequence.hpp>
#include <sge/model/md3/load_flags_field.hpp>
#include <sge/model/md3/loader.hpp>
#include <sge/model/md3/loader_unique_ptr.hpp>
#include <sge/model/md3/normal_sequence.hpp>
#include <sge/model/md3/object.hpp>
#include <sge/model/md3/part_name_sequence.hpp>
#include <sge/model/md3/string.hpp>
#include <sge/model/md3/vertex_sequence.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/clear/depth_buffer_value.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/event/render.hpp>
#include <sge/renderer/index/buffer.hpp>
#include <sge/renderer/index/buffer_parameters.hpp>
#include <sge/renderer/index/buffer_unique_ptr.hpp>
#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/index/format_16.hpp>
#include <sge/renderer/index/i16.hpp>
#include <sge/renderer/index/iterator.hpp>
#include <sge/renderer/index/scoped_lock.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/index/dynamic/view.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/state/core/blend/alpha_off.hpp>
#include <sge/renderer/state/core/blend/alpha_variant.hpp>
#include <sge/renderer/state/core/blend/object.hpp>
#include <sge/renderer/state/core/blend/object_unique_ptr.hpp>
#include <sge/renderer/state/core/blend/parameters.hpp>
#include <sge/renderer/state/core/blend/scoped.hpp>
#include <sge/renderer/state/core/blend/write_alpha.hpp>
#include <sge/renderer/state/core/blend/write_blue.hpp>
#include <sge/renderer/state/core/blend/write_green.hpp>
#include <sge/renderer/state/core/blend/write_mask.hpp>
#include <sge/renderer/state/core/blend/write_red.hpp>
#include <sge/renderer/state/core/depth_stencil/object.hpp>
#include <sge/renderer/state/core/depth_stencil/object_unique_ptr.hpp>
#include <sge/renderer/state/core/depth_stencil/parameters.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/enabled.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/func.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/variant.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/write_enable.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/off.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/variant.hpp>
#include <sge/renderer/state/core/rasterizer/cull_mode.hpp>
#include <sge/renderer/state/core/rasterizer/enable_scissor_test.hpp>
#include <sge/renderer/state/core/rasterizer/fill_mode.hpp>
#include <sge/renderer/state/core/rasterizer/object.hpp>
#include <sge/renderer/state/core/rasterizer/object_unique_ptr.hpp>
#include <sge/renderer/state/core/rasterizer/parameters.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <sge/renderer/state/ffp/transform/scoped.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/buffer_parameters.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vertex/scoped_buffer.hpp>
#include <sge/renderer/vertex/scoped_declaration.hpp>
#include <sge/renderer/vertex/scoped_lock.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/normal.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/make_part_index.hpp>
#include <sge/systems/config.hpp>
#include <sge/systems/cursor_option.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/log_settings.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/window_source.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/window/loop.hpp>
#include <sge/window/loop_function.hpp>
#include <sge/window/title.hpp>
#include <awl/show_error.hpp>
#include <awl/show_error_narrow.hpp>
#include <awl/show_message.hpp>
#include <awl/event/base.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/exit_success.hpp>
#include <awl/main/function_context.hpp>
#include <fcppt/args_from_second.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/container/maybe_front.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/math/deg_to_rad.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/rotation_x.hpp>
#include <fcppt/math/matrix/rotation_y.hpp>
#include <fcppt/math/matrix/rotation_z.hpp>
#include <fcppt/math/matrix/row.hpp>
#include <fcppt/math/matrix/static.hpp>
#include <fcppt/math/matrix/translation.hpp>
#include <fcppt/math/matrix/vector.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/options/apply.hpp>
#include <fcppt/options/default_help_switch.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/help_text.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/make_default_value.hpp>
#include <fcppt/options/option.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/optional_short_name.hpp>
#include <fcppt/options/parse_help.hpp>
#include <fcppt/options/result.hpp>
#include <fcppt/options/result_of.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_real.hpp>
#include <fcppt/random/generator/minstd_rand.hpp>
#include <fcppt/random/generator/seed_from_chrono.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/record/permute.hpp>
#include <fcppt/record/variadic.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/variant/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/list/list.hpp>
#include <chrono>
#include <cmath>
#include <example_main.hpp>
#include <exception>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>


/**
	Example description:

	This example implements anaglyph 3D, which means you have to buy
	red/cyan 3D glasses to enjoy it. When running it (with default
	parameters), you should be able to look around with the mouse, as
	well as move around with w, a, s and d. You should see "arrow"
	models at various locations and in various orientations around the
	"spawn point".

	Anaglyph 3D is achieved by rendering each object twice: From the
	left eye and from the right eye. The left eye is rendered in red,
	the right eye in cyan.
 */


namespace
{
// Define the vertex format which consists of a position value and a normal (for the diffuse shading)
namespace vf
{
typedef
sge::renderer::vf::pos<
	sge::renderer::scalar,
	3
>
position;

typedef
sge::renderer::vf::normal<
	sge::renderer::scalar
>
normal;

typedef
sge::renderer::vf::part<
	metal::list<
		position,
		normal
	>
>
format_part;

typedef
sge::renderer::vf::format<
	metal::list<
		format_part
	>
>
format;

typedef
sge::renderer::vf::view<
	format_part
>
format_part_view;

}

// This class is just a wrapper around a vertex buffer and an index
// buffer. It receives the loaded md3 model and "compiles" both
// buffers from it.
class compiled_model
{
	FCPPT_NONCOPYABLE(
		compiled_model
	);
public:
	compiled_model(
		sge::renderer::device::core &,
		sge::renderer::vertex::declaration const &,
		sge::model::md3::object const &
	);

	sge::renderer::vertex::buffer const &
	vb() const;

	void
	render(
		sge::renderer::context::core &
	) const;

	~compiled_model();
private:
	compiled_model(
		sge::renderer::device::core &,
		sge::renderer::vertex::declaration const &,
		sge::model::md3::object const &,
		sge::model::md3::string const &
	);

	sge::renderer::device::core &renderer_;

	sge::renderer::vertex::buffer_unique_ptr const vb_;

	sge::renderer::index::buffer_unique_ptr const ib_;
};

compiled_model::compiled_model(
	sge::renderer::device::core &_renderer,
	sge::renderer::vertex::declaration const &_vd,
	sge::model::md3::object const &_model
)
:
	compiled_model(
		_renderer,
		_vd,
		_model,
		[
			&_model
		]()
		->
		sge::model::md3::string
		{
			sge::model::md3::part_name_sequence const parts(
				_model.part_names()
			);

			return
				sge::model::md3::string(
					FCPPT_ASSERT_OPTIONAL_ERROR(
						fcppt::container::maybe_front(
							parts
						)
					).get()
				);
		}()
	)
{
}

sge::renderer::vertex::buffer const &
compiled_model::vb() const
{
	return
		*vb_;
}

void
compiled_model::render(
	sge::renderer::context::core &_context
) const
{
	// This should be pretty self-explanatory. Note that here, we just
	// call render. The vertex buffer isn't activated here, neither is
	// the vertex declaration. This is done at a "higher" level so we
	// don't activate/deactive it too often (which decreases
	// performance).
	_context.render_indexed(
		*ib_,
		sge::renderer::vertex::first(
			0u
		),
		sge::renderer::vertex::count(
			vb_->linear_size()
		),
		sge::renderer::primitive_type::triangle_list,
		sge::renderer::index::first(
			0u
		),
		sge::renderer::index::count(
			ib_->linear_size()
		)
	);
}

compiled_model::~compiled_model()
{
}

compiled_model::compiled_model(
	sge::renderer::device::core &_renderer,
	sge::renderer::vertex::declaration const &_vd,
	sge::model::md3::object const &_model,
	sge::model::md3::string const &_first_part
)
:
	renderer_{
		_renderer
	},
	vb_(
		renderer_.create_vertex_buffer(
			sge::renderer::vertex::buffer_parameters(
				_vd,
				sge::renderer::vf::dynamic::make_part_index<
					vf::format,
					vf::format_part
				>(),
				sge::renderer::vertex::count(
					_model.vertices(
						_first_part
					).size()
				),
				sge::renderer::resource_flags_field::null()
			)
		)
	),
	// Create the index buffer. We have to decide which data type to
	// use. Since our models have < 100 vertices, a 16 bit integer is
	// enough, so we're using "format::i16" here.
	ib_(
		renderer_.create_index_buffer(
			sge::renderer::index::buffer_parameters(
				sge::renderer::index::dynamic::format::i16,
				sge::renderer::index::count(
					_model.indices(
						_first_part
					).size()
				),
				sge::renderer::resource_flags_field::null()
			)
		)
	)
{
	{
		sge::renderer::vertex::scoped_lock const vblock{
			*vb_,
			sge::renderer::lock_mode::writeonly
		};

		vf::format_part_view const current_vertex_view{
			vblock.value()
		};

		vf::format_part_view::iterator current_vertex{
			current_vertex_view.begin()
		};

		sge::model::md3::vertex_sequence const model_vertices{
			_model.vertices(
				_first_part
			)
		};

		sge::model::md3::normal_sequence const model_normals{
			FCPPT_ASSERT_OPTIONAL_ERROR(
				_model.normals(
					_first_part
				)
			)
		};

		sge::model::md3::normal_sequence::const_iterator current_model_normal{
			model_normals.begin()
		};

		for(
			auto const &model_vertex
			:
			model_vertices
		)
		{
			(*current_vertex).set<
				vf::position
			>(
				fcppt::math::vector::structure_cast<
					vf::position::packed_type,
					fcppt::cast::size_fun
				>(
					model_vertex
				)
			);

			(*current_vertex++).set<
				vf::normal
			>(
				fcppt::math::vector::structure_cast<
					vf::normal::packed_type,
					fcppt::cast::size_fun
				>(
					*current_model_normal++
				)
			);
		}
	}

	sge::renderer::index::scoped_lock const iblock{
		*ib_,
		sge::renderer::lock_mode::writeonly
	};

	sge::renderer::index::dynamic::view const indices(
		iblock.value());

	sge::renderer::index::iterator<
		sge::renderer::index::format_16
	> current_index(
		indices.data()
	);

	sge::model::md3::index_sequence const model_indices{
		_model.indices(
			_first_part
		)
	};

	for(
		auto const index
		:
		model_indices
	)
		(*current_index++).set(
			fcppt::cast::size<
				sge::renderer::index::i16
			>(
				index
			)
		);
}


// This is a specific model instance, meaning it has a position and an
// orientation. It has no logic, however.
class model_instance
{
	FCPPT_NONCOPYABLE(
		model_instance
	);
public:
	model_instance(
		compiled_model const &,
		sge::renderer::matrix4 const &
	);

	void
	render(
		sge::renderer::context::core &
	);

	sge::renderer::matrix4 const &
	modelview() const;

	~model_instance();
private:
	compiled_model const &backend_;

	sge::renderer::matrix4 const modelview_;
};

model_instance::model_instance(
	compiled_model const &_backend,
	sge::renderer::matrix4 const &_modelview
)
:
	backend_{
		_backend
	},
	modelview_{
		_modelview
	}
{
}

void
model_instance::render(
	sge::renderer::context::core &_context
)
{
	backend_.render(
		_context
	);
}

sge::renderer::matrix4 const &
model_instance::modelview() const
{
	return
		modelview_;
}

model_instance::~model_instance()
{
}

// This class represents a collection of randomly placed and oriented
// "model_instance" objects (see above).
class random_model_collection
{
	FCPPT_NONCOPYABLE(
		random_model_collection
	);
public:
	random_model_collection(
		sge::renderer::device::ffp &,
		compiled_model const &
	);

	void
	render(
		sge::renderer::context::ffp &,
		sge::renderer::matrix4 const &
	);

	~random_model_collection();
private:
	typedef
	fcppt::unique_ptr<
		model_instance
	>
	model_instance_unique_ptr;

	typedef
	std::vector<
		model_instance_unique_ptr
	>
	model_sequence;

	sge::renderer::device::ffp &renderer_;

	compiled_model const &backend_;

	model_sequence models_;
};

random_model_collection::random_model_collection(
	sge::renderer::device::ffp &_renderer,
	compiled_model const &_backend
)
:
	renderer_{
		_renderer
	},
	backend_{
		_backend
	},
	models_{
		[
			&_backend
		]{
			// Create objects in the cube with side length 10
			sge::renderer::scalar const position_range{
				fcppt::literal<
					sge::renderer::scalar
				>(
					10
				)
			};

			// See the fcppt documentation on how this really works.
			typedef
			fcppt::random::generator::minstd_rand
			generator_type;

			generator_type generator{
				fcppt::random::generator::seed_from_chrono<
					generator_type::seed
				>()
			};

			typedef
			fcppt::random::distribution::basic<
				fcppt::random::distribution::parameters::uniform_real<
					sge::renderer::scalar
				>
			>
			distribution;

			typedef
			fcppt::random::variate<
				generator_type,
				distribution
			>
			variate;

			variate position_rng{
				generator,
				distribution{
					distribution::param_type::min{
						-position_range
					},
					distribution::param_type::sup{
						position_range
					}
				}
			};

			variate angle_rng{
				generator,
				distribution{
					distribution::param_type::min{
						0.f
					},
					distribution::param_type::sup{
						fcppt::math::twopi<
							sge::renderer::scalar
						>()
					}
				}
			};

			return
				fcppt::algorithm::map<
					model_sequence
				>(
					fcppt::make_int_range_count(
						100
					),
					[
						&_backend,
						&angle_rng,
						&position_rng
					](
						auto const
					)
					{
						return
							fcppt::make_unique_ptr<
								model_instance
							>(
								_backend,
								fcppt::math::matrix::rotation_x(
									angle_rng()
								)
								*
								fcppt::math::matrix::rotation_y(
									angle_rng()
								)
								*
								fcppt::math::matrix::rotation_z(
									angle_rng()
								)
								*
								fcppt::math::matrix::translation(
									sge::renderer::vector3{
										position_rng(),
										position_rng(),
										position_rng()
									}
								)
							);
					}
				);
		}()
	}
{
}

void
random_model_collection::render(
	sge::renderer::context::ffp &_context,
	sge::renderer::matrix4 const &_mv
)
{
	// Finally, we activate the vertex buffer so we can render stuff
	// with it. We only activate it once, however, not for every model.
	sge::renderer::vertex::scoped_buffer const scoped_vb{
		_context,
		backend_.vb()
	};

	for(
		auto const &current_model
		:
		models_
	)
	{
		sge::renderer::state::ffp::transform::object_unique_ptr const world_state{
			renderer_.create_transform_state(
				sge::renderer::state::ffp::transform::parameters{
					_mv * current_model->modelview()
				}
			)
		};

		// Set the world transformation and render
		sge::renderer::state::ffp::transform::scoped const world_transform{
			_context,
			sge::renderer::state::ffp::transform::mode::world,
			*world_state
		};

		current_model->render(
			_context
		);
	}
}

random_model_collection::~random_model_collection()
{
}

// Rendering works as follows:
// The camera gives us a coordinate system consisting of three vectors: right, up, and forward:
//
// .oO(The following ascii art is probably screwed up if you're using a non-monospace font)
//     ^
//     |
//     | forward
//     |
// up  +-----> right
//
// We want to emulate a person looking straight ahead (along the
// forward vector) with two eyes, focusing an object at distance
// 'f'. The distance between the eyes is 'd'. So we have:
//          x
//   |     / \     |
//   |    /   \    |
//   |   /  ^  \   |  f
//   |  /   |   \ a|
//   | /    |    \ |
//   |/     |     \|
//   y      +----->z
//    <---->
//      d/2
//
// Here, 'y' and 'z' are the two eyes, focusing the object at location 'x'.
// Now, rendering is just:
//
// - Translate d/2 along the "right" vector
// - Rotate the coordinate system around the "up" vector with angle 'a'
//
// Using simple trigonometry, we get "atan(f/(d/2))" for 'a'
// The following function implements just this.

sge::camera::coordinate_system::object
move_eye_position(
	sge::camera::coordinate_system::object _result,
	sge::renderer::scalar const _eye_distance,
	sge::renderer::scalar const _focal_length
)
{
	_result.position(
		sge::camera::coordinate_system::position(
			_result.position().get()
			+
			_eye_distance
			*
			_result.right().get()
		)
	);

	sge::renderer::scalar const
		angle{
			std::atan(
				_eye_distance
				/
				_focal_length
			)
		},
		sinx{
			std::sin(
				angle
			)
		},
		cosx{
			std::cos(
				angle
			)
		},
		cosxc{
			1 - cosx
		},
		x{
			_result.up().get().x()
		},
		y{
			_result.up().get().y()
		},
		z{
			_result.up().get().z()
		};

	typedef
	fcppt::math::matrix::static_<
		sge::renderer::scalar,
		3,
		3
	>
	matrix3;

	matrix3 const rotation_matrix{
		fcppt::math::matrix::row(
			cosx + x*x*cosxc,   x*y*cosxc - z*sinx, x*z*cosxc + y*sinx
		),
		fcppt::math::matrix::row(
			x*y*cosxc + z*sinx, cosx + y*y*cosxc,   y*z*cosxc - x*sinx
		),
		fcppt::math::matrix::row(
			x*z*cosxc - y*sinx, y*z*cosxc + x*sinx, cosx + z*z*cosxc
		)
	};

	_result.right(
		sge::camera::coordinate_system::right(
			rotation_matrix * _result.right().get()
		)
	);

	_result.forward(
		sge::camera::coordinate_system::forward(
			rotation_matrix * _result.forward().get()
		)
	);

	return
		_result;
}

FCPPT_RECORD_MAKE_LABEL(
	eye_distance_label
);

FCPPT_RECORD_MAKE_LABEL(
	focal_length_label
);

typedef
fcppt::record::variadic<
	fcppt::record::element<
		eye_distance_label,
		sge::renderer::scalar
	>,
	fcppt::record::element<
		focal_length_label,
		sge::renderer::scalar
	>
>
options_record;

awl::main::exit_code const
main_program(
	options_record const &_options
)
{
	sge::systems::instance<
		metal::list<
			sge::systems::with_renderer<
				sge::systems::renderer_caps::ffp
			>,
			sge::systems::with_window,
			sge::systems::with_input
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::systems::window_source(
					sge::systems::original_window(
						sge::window::title(
							FCPPT_TEXT("sge test for anaglyph 3D")
						)
					)
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::pixel_format::object(
					sge::renderer::pixel_format::color::depth32,
					sge::renderer::pixel_format::depth_stencil::d24,
					sge::renderer::pixel_format::optional_multi_samples(),
					sge::renderer::pixel_format::srgb::no
				),
				sge::renderer::display_mode::parameters(
					sge::renderer::display_mode::vsync::on,
					sge::renderer::display_mode::optional_object()
				),
				sge::viewport::optional_resize_callback{
					sge::viewport::fill_on_resize()
				}
			)
		)
		(
			sge::systems::input(
				sge::systems::cursor_option_field{
					sge::systems::cursor_option::exclusive
				}
			)
		)
		(
			sge::systems::config()
			.log_settings(
				sge::systems::log_settings{
					sge::log::option_container{
						sge::log::option{
							sge::log::location(),
							fcppt::log::level::debug
						}
					}
				}
			)
		)
	);

	sge::camera::first_person::object camera{
		sge::camera::first_person::parameters{
			sge::camera::first_person::movement_speed(
				4.0f
			),
			sge::camera::coordinate_system::identity()
		}
	};

	sge::camera::perspective_projection_from_viewport camera_viewport_connection(
		camera,
		sys.viewport_manager(),
		sge::renderer::projection::near(
			0.1f
		),
		sge::renderer::projection::far(
			1000.f
		),
		sge::renderer::projection::fov(
			fcppt::math::deg_to_rad(
				90.f
			)
		)
	);

	sge::renderer::vertex::declaration_unique_ptr const vertex_declaration(
		sys.renderer_device_ffp().create_vertex_declaration(
			sge::renderer::vertex::declaration_parameters(
				sge::renderer::vf::dynamic::make_format<
					vf::format
				>()
			)
		)
	);

	// Create an md3 loader using the "create" function.
	sge::model::md3::loader_unique_ptr const md3_loader(
		sge::model::md3::create(
			sys.log_context()
		)
	);

	// Create a model and a model collection
	compiled_model main_model(
		sys.renderer_device_ffp(),
		*vertex_declaration,
		*md3_loader->load(
			sge::config::media_path()
			/
			FCPPT_TEXT("md3s")
			/
			FCPPT_TEXT("arrow.md3"),
			sge::model::md3::load_flags_field::null()
		)
	);

	random_model_collection model_collection(
		sys.renderer_device_ffp(),
		main_model
	);

	sge::timer::basic<
		sge::timer::clocks::standard
	> camera_timer(
		sge::timer::parameters<
			sge::timer::clocks::standard
		>(
			std::chrono::seconds(
				1
			)
		)
	);

	sge::renderer::state::core::depth_stencil::object_unique_ptr const depth_stencil_state(
		sys.renderer_device_core().create_depth_stencil_state(
			sge::renderer::state::core::depth_stencil::parameters(
				sge::renderer::state::core::depth_stencil::depth::variant(
					sge::renderer::state::core::depth_stencil::depth::enabled(
						sge::renderer::state::core::depth_stencil::depth::func::less,
						sge::renderer::state::core::depth_stencil::depth::write_enable(
							true
						)
					)
				),
				sge::renderer::state::core::depth_stencil::stencil::variant(
					sge::renderer::state::core::depth_stencil::stencil::off()
				)
			)
		)
	);

	sge::renderer::state::core::rasterizer::object_unique_ptr const rasterizer_state(
		sys.renderer_device_core().create_rasterizer_state(
			sge::renderer::state::core::rasterizer::parameters(
				sge::renderer::state::core::rasterizer::cull_mode::counter_clockwise,
				sge::renderer::state::core::rasterizer::fill_mode::solid,
				sge::renderer::state::core::rasterizer::enable_scissor_test(
					false
				)
			)
		)
	);

	sge::renderer::state::core::blend::object_unique_ptr const blend_red_state(
		sys.renderer_device_core().create_blend_state(
			sge::renderer::state::core::blend::parameters(
				sge::renderer::state::core::blend::alpha_variant(
					sge::renderer::state::core::blend::alpha_off()
				),
				sge::renderer::state::core::blend::write_mask(
					sge::renderer::state::core::blend::write_red(
						true
					),
					sge::renderer::state::core::blend::write_blue(
						false
					),
					sge::renderer::state::core::blend::write_green(
						false
					),
					sge::renderer::state::core::blend::write_alpha(
						true
					)
				)
			)
		)
	);

	sge::renderer::state::core::blend::object_unique_ptr const blend_cyan_state(
		sys.renderer_device_core().create_blend_state(
			sge::renderer::state::core::blend::parameters(
				sge::renderer::state::core::blend::alpha_variant(
					sge::renderer::state::core::blend::alpha_off()
				),
				sge::renderer::state::core::blend::write_mask(
					sge::renderer::state::core::blend::write_red(
						false
					),
					sge::renderer::state::core::blend::write_blue(
						true
					),
					sge::renderer::state::core::blend::write_green(
						true
					),
					sge::renderer::state::core::blend::write_alpha(
						true
					)
				)
			)
		)
	);

	sge::renderer::scalar const eye_distance{
		fcppt::record::get<
			eye_distance_label
		>(
			_options
		)
	};

	sge::renderer::scalar const focal_length{
		fcppt::record::get<
			focal_length_label
		>(
			_options
		)
	};

	sge::renderer::clear::depth_buffer_value const depth_clear_value(
		1.f
	);

	auto const draw_camera(
		[
			&blend_cyan_state,
			&blend_red_state,
			&camera,
			depth_clear_value,
			eye_distance,
			focal_length,
			&model_collection,
			&sys,
			&vertex_declaration
		](
			sge::renderer::context::ffp &_context,
			sge::camera::projection_matrix const &_projection
		)
		{

			sge::renderer::state::ffp::transform::object_unique_ptr const projection_state(
				sys.renderer_device_ffp().create_transform_state(
					sge::renderer::state::ffp::transform::parameters(
						_projection.get()
					)
				)
			);

			sge::renderer::state::ffp::transform::scoped const projection_transform(
				_context,
				sge::renderer::state::ffp::transform::mode::projection,
				*projection_state
			);

			// The vertex declaration can be set once in this case
			sge::renderer::vertex::scoped_declaration const scoped_vd(
				_context,
				*vertex_declaration
			);

			{
				// Set the color mask to "red"
				sge::renderer::state::core::blend::scoped const scoped_blend(
					_context,
					*blend_red_state
				);

				model_collection.render(
					_context,
					sge::camera::matrix_conversion::world(
						move_eye_position(
							camera.coordinate_system(),
							eye_distance,
							focal_length
						)
					)
				);
			}

			// Clear depth buffer
			_context.clear(
				sge::renderer::clear::parameters()
				.depth_buffer(
					depth_clear_value
				)
			);

			{
				// Set the color mask to cyan
				sge::renderer::state::core::blend::scoped const scoped_blend(
					_context,
					*blend_cyan_state
				);

				model_collection.render(
					_context,
					sge::camera::matrix_conversion::world(
						move_eye_position(
							camera.coordinate_system(),
							-eye_distance,
							focal_length
						)
					)
				);
			}
		}
	);

	auto const draw(
		[
			&camera,
			&camera_timer,
			&draw_camera,
			depth_clear_value,
			&sys
		]
		{
			// This moves the camera around
			camera.update(
				std::chrono::duration_cast<
					sge::camera::update_duration
				>(
					sge::timer::elapsed_and_reset(
						camera_timer
					)
				)
			);

			sge::renderer::context::scoped_ffp const scoped_block(
				sys.renderer_device_ffp(),
				sys.renderer_device_ffp().onscreen_target()
			);

			sge::renderer::context::ffp &context(
				scoped_block.get()
			);

			context.clear(
				sge::renderer::clear::parameters()
				.back_buffer(
					sge::image::color::any::object{
						sge::image::color::predef::black()
					}
				)
				.depth_buffer(
					depth_clear_value
				)
			);

			fcppt::optional::maybe_void(
				camera.projection_matrix(),
				[
					&context,
					&draw_camera
				](
					sge::camera::projection_matrix const &_projection
				)
				{
					draw_camera(
						context,
						_projection
					);
				}
			);
		}
	);

	return
		sge::window::loop(
			sys.window_system(),
			sge::window::loop_function{
				[
					&sys,
					&camera,
					&draw
				](
					awl::event::base const &_event
				)
				{
					sge::systems::quit_on_escape(
						sys,
						_event
					);

					fcppt::optional::maybe_void(
						fcppt::variant::dynamic_cast_<
							metal::list<
								sge::renderer::event::render const,
								sge::input::event_base const
							>,
							fcppt::cast::dynamic_fun
						>(
							_event
						),
						[
							&camera,
							&draw
						](
							auto const &_variant
						)
						{
							fcppt::variant::match(
								_variant,
								[
									&draw
								](
									fcppt::reference<
										sge::renderer::event::render const
									>
								)
								{
									draw();
								},
								[
									&camera
								](
									fcppt::reference<
										sge::input::event_base const
									> const _input_event
								)
								{
									camera.process_event(
										_input_event.get()
									);
								}
							);
						}
					);
				}
			}
		);
}

}

awl::main::exit_code const
example_main(
	awl::main::function_context const &_function_context
)
try
{
	auto const parser(
		fcppt::options::apply(
			fcppt::options::option<
				eye_distance_label,
				sge::renderer::scalar
			>{
				fcppt::options::optional_short_name{},
				fcppt::options::long_name{
					FCPPT_TEXT("eye-distance")
				},
				fcppt::options::make_default_value(
					fcppt::optional::make(
						fcppt::literal<
							sge::renderer::scalar
						>(
							0.01
						)
					)
				),
				fcppt::options::optional_help_text{}
			},
			fcppt::options::option<
				focal_length_label,
				sge::renderer::scalar
			>{
				fcppt::options::optional_short_name{},
				fcppt::options::long_name{
					FCPPT_TEXT("focal-length")
				},
				fcppt::options::make_default_value(
					fcppt::optional::make(
						fcppt::literal<
							sge::renderer::scalar
						>(
							1
						)
					)
				),
				fcppt::options::optional_help_text{}
			}
		)
	);

	typedef
	decltype(
		parser
	)
	parser_type;

	return
		fcppt::variant::match(
			fcppt::options::parse_help(
				fcppt::options::default_help_switch(),
				parser,
				fcppt::args_from_second(
					_function_context.argc(),
					_function_context.argv()
				)
			),
			[](
				fcppt::options::result<
					fcppt::options::result_of<
						parser_type
					>
				> const &_result
			)
			{
				return
					fcppt::either::match(
						_result,
						[](
							fcppt::options::error const &_error
						)
						-> awl::main::exit_code
						{
							awl::show_error(
								fcppt::output_to_fcppt_string(
									_error
								)
							);

							return
								awl::main::exit_failure();
						},
						[](
							fcppt::options::result_of<
								parser_type
							> const &_args
						)
						-> awl::main::exit_code
						{
							return
								main_program(
									fcppt::record::permute<
										options_record
									>(
										_args
									)
								);
						}
					);
			},
			[](
				fcppt::options::help_text const &_help_text
			)
			{
				awl::show_message(
					fcppt::output_to_fcppt_string(
						_help_text
					)
				);

				return
					awl::main::exit_success();
			}
		);
}
catch(
	fcppt::exception const &_error
)
{
	awl::show_error(
		_error.string()
	);

	return
		awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	awl::show_error_narrow(
		_error.what()
	);

	return
		awl::main::exit_failure();
}
