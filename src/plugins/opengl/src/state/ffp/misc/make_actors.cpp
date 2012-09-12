	case rs::normalize_normals:
		sge::opengl::enable_bool(
			sge::opengl::state::convert::bool_(
				_state.state()
			),
			_state.value()
		);
		return;

		sge::opengl::state::point_sprite(
			_parameters.system_context(),
			_state.value()
		);
	case rs::local_viewer:
		{
			GLint const value(
				_state.value()
				?
					1
				:
					0
			);

			::glLightModeliv(
				GL_LIGHT_MODEL_LOCAL_VIEWER,
				&value
			);

			SGE_OPENGL_CHECK_STATE(
				FCPPT_TEXT("glLightModeliv failed"),
				sge::renderer::exception
			)
		}

