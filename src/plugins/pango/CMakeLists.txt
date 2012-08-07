set(
	SGE_PANGO_FILES
	src/plugins/pango/include/sge/pango/convert/alignment.hpp
	src/plugins/pango/include/sge/pango/convert/from_rect.hpp
	src/plugins/pango/include/sge/pango/convert/to_unit.hpp
	src/plugins/pango/include/sge/pango/create_layout.hpp
	src/plugins/pango/include/sge/pango/create_text_layout.hpp
	src/plugins/pango/include/sge/pango/font_description.hpp
	src/plugins/pango/include/sge/pango/freetype/make_bitmap.hpp
	src/plugins/pango/include/sge/pango/glib_deleter.hpp
	src/plugins/pango/include/sge/pango/glib_deleter_fwd.hpp
	src/plugins/pango/include/sge/pango/ink_rect.hpp
	src/plugins/pango/include/sge/pango/object.hpp
	src/plugins/pango/include/sge/pango/pango_layout_scoped_ptr.hpp
	src/plugins/pango/include/sge/pango/pango_layout_unique_ptr.hpp
	src/plugins/pango/include/sge/pango/system.hpp
	src/plugins/pango/include/sge/pango/text.hpp
	src/plugins/pango/src/convert/alignment.cpp
	src/plugins/pango/src/convert/from_rect.cpp
	src/plugins/pango/src/convert/to_unit.cpp
	src/plugins/pango/src/create_layout.cpp
	src/plugins/pango/src/create_text_layout.cpp
	src/plugins/pango/src/exports.cpp
	src/plugins/pango/src/font_description.cpp
	src/plugins/pango/src/freetype/make_bitmap.cpp
	src/plugins/pango/src/glib_deleter.cpp
	src/plugins/pango/src/ink_rect.cpp
	src/plugins/pango/src/object.cpp
	src/plugins/pango/src/system.cpp
	src/plugins/pango/src/text.cpp
)

include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)

include_directories(
	${FCPPT_UTILS_INCLUDE_SYSTEM}
	${PANGO_INCLUDE_DIRS}
)

link_directories(
	${PANGO_LIBRARY_DIRS}
)

add_definitions(
	${PANGO_CFLAGS}
)

add_sge_plugin(
	pango
	"sgecharconv;sgefont;sgeimage2d;sgeplugin"
	"${PANGO_LIBRARIES}"
)
