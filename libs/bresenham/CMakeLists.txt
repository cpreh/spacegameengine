set(
	SGE_BRESENHAM_FILES
	libs/bresenham/include/sge/bresenham/detail/impl.hpp
	libs/bresenham/include/sge/bresenham/detail/thick.hpp
	libs/bresenham/include/sge/bresenham/normal.hpp
	libs/bresenham/include/sge/bresenham/thick.hpp
)

add_sge_dummy_library(
	bresenham
	TRANSITIVE_ADDITIONAL_DEPS
		fcppt_core_interface
)
