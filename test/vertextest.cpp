#include <sge/init.hpp>
#include <sge/systems.hpp>
#include <sge/iostream.hpp>
#include <sge/text.hpp>
#include <sge/exception.hpp>
#include <sge/su.hpp>
#include <sge/renderer/vf/make_dynamic_format.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <boost/mpl/vector.hpp>
#include <ostream>
#include <exception>
#include <cstdlib>

struct print_vector {
	template<typename T>
	void operator()(
		T &t) const
	{
		sge::cerr << t << ' ';
	}
};

int main()
try
{
	sge::systems sys;
	sys.init<sge::init::core>();
	sys.init<sge::init::renderer>(
		sge::renderer::screen_size_t(1024, 768));
	sys.init<sge::init::input>();

	typedef sge::renderer::vf::pos<
		sge::space_unit,
		2
	> pos_type;

	typedef sge::renderer::vf::pos<
		sge::space_unit,
		3
	> pos3_type;

	typedef sge::renderer::vf::format<
		boost::mpl::vector<
			pos_type,
			pos_type,
			pos3_type
		>
	> format;

	typedef boost::mpl::transform<
		format::elements,
		sge::renderer::vf::element_stride<
			boost::mpl::_1
		>
	>::type strides;

	typedef sge::partial_sums<
		strides
	>::type offsets;

	sge::renderer::vf::dynamic_format const dyn_fmt(
		sge::renderer::vf::make_dynamic_format<
			format>());
	
	unsigned char test[1000];
	sge::renderer::vf::dynamic_view const dyn_view(
		test,
		1,
		dyn_fmt);
	
	typedef sge::renderer::vf::view<
		format
	> view;

	/*view v(dyn_view);
	
	
	v.begin()->set<pos_type>(
		sge::math::vector2(
			sge::su(0),
			sge::su(0)));*/
	//typedef view::iterator::value_type vertex_type;

	typedef sge::renderer::vf::vertex<
		format
	> vertex_type;

	boost::mpl::for_each<
		//offsets>(
		vertex_type::offsets>(
			print_vector());
	sge::cerr << '\n';


	vertex_type vert(test);
	vert.set<pos_type>(
		sge::math::vector2(
			sge::su(0),
			sge::su(0)));
}
catch(sge::exception const &e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
