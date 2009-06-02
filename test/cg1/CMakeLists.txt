MACRO (ADD_SGE_CG1_TEST name)
	ADD_EXECUTABLE (sgecg1${name} ${name}.cpp)
	TARGET_LINK_LIBRARIES (sgecg1${name} sgecore)
ENDMACRO()

ADD_SGE_CG1_TEST(ex04)
