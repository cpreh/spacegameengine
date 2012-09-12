	image::color::rgba32f const fcolor(
		image::color::any::convert<
			image::color::rgba32f_format
		>(
			_state.value()
		)
	);

	case rs::fog_color:
		::glFogfv(
			GL_FOG_COLOR,
			fcolor.data()
		);

		SGE_OPENGL_CHECK_STATE(
			FCPPT_TEXT("glFogfv failed"),
			sge::renderer::exception
		)

		return;

