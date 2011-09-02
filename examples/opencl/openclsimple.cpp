#include <sge/opencl/system.hpp>
#include <sge/opencl/platform/object.hpp>
#include <sge/opencl/context/parameters.hpp>
#include <sge/opencl/context/object.hpp>
#include <sge/opencl/device/object_ref_sequence.hpp>
#include <CL/cl.h>
#include <fcppt/text.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/io/cin.hpp>
#include <fcppt/io/cout.hpp>
#include <boost/algorithm/string/join.hpp>
#include <iostream>
#include <ostream>
#include <string>
#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <limits>

namespace
{
template<typename T,typename Char,typename Traits>
T const
query_value_from_user(
	std::basic_istream<Char,Traits> &stream)
{
	T result;
	while(!(stream >> result))
	{
		if(stream.eof())
			throw fcppt::exception(FCPPT_TEXT("Couldn't read value, EOF was reached first."));
		stream.clear();
		stream.ignore(
			std::numeric_limits<std::streamsize>::max(),
			stream.widen('\n'));
		std::cerr << "before next iteration\n";
	}
	return result;
}
}

int
main()
try
{

	sge::opencl::system opencl_system;

	fcppt::io::cout << FCPPT_TEXT("Querying the number of available platforms...\n");

	sge::opencl::platform::object_sequence &platforms(
		opencl_system.platforms());

	if(platforms.empty())
	{
		fcppt::io::cerr << FCPPT_TEXT("Couldn't find any OpenCL platforms on your system.\n");
		return EXIT_FAILURE;
	}

	fcppt::io::cout << FCPPT_TEXT("Number of OpenCL platforms: ") << platforms.size() << FCPPT_TEXT("\n");
	fcppt::io::cout << FCPPT_TEXT("Platform listing begin:\n");
	fcppt::io::cout << FCPPT_TEXT("-----------------------\n");

	sge::opencl::platform::object_sequence::size_type platform_index = 0;
	for(
		sge::opencl::platform::object_sequence::const_iterator current_platform =
			platforms.begin();
		current_platform != platforms.end();
		++current_platform)
	{
		fcppt::io::cout << FCPPT_TEXT("\tPlatform ") << platform_index << FCPPT_TEXT(":\n");
		fcppt::io::cout
			<< FCPPT_TEXT("\tName: ")
			<< current_platform->name()
			<< FCPPT_TEXT("\n");

		fcppt::io::cout
			<< FCPPT_TEXT("\tVendor: ")
			<< current_platform->vendor()
			<< FCPPT_TEXT("\n");

		fcppt::io::cout
			<< FCPPT_TEXT("Profile type: ")
			<<
				(current_platform->profile() == sge::opencl::profile_type::full
				?
					fcppt::string(FCPPT_TEXT("full"))
				:
					fcppt::string(FCPPT_TEXT("embedded")))
			<< FCPPT_TEXT("\n");

		fcppt::io::cout
			<< FCPPT_TEXT("\tVersion: ")
			<< current_platform->version().major_part()
			<< FCPPT_TEXT(".")
			<< current_platform->version().minor_part()
			<< FCPPT_TEXT("\n");

		if(!current_platform->version().platform_specific().empty())
			fcppt::io::cout
				<< FCPPT_TEXT("\tPlatform specific version info: ")
				<< fcppt::from_std_string(current_platform->version().platform_specific())
				<< FCPPT_TEXT("\n");

		fcppt::io::cout << FCPPT_TEXT("\tExtension list begin:\n");
		fcppt::io::cout << FCPPT_TEXT("\t*********************\n");
		fcppt::io::cout
			<< FCPPT_TEXT("\t\t")
			<<
				fcppt::from_std_string(
					boost::algorithm::join(
						current_platform->extensions(),
						std::string("\n\t\t")));
		fcppt::io::cout << FCPPT_TEXT("\r\t*********************\n");
		fcppt::io::cout << FCPPT_TEXT("-----------------------\n");
	}

	fcppt::io::cout << FCPPT_TEXT("Platform listing end\n");

	sge::opencl::platform::object_sequence::size_type chosen_platform_index;
	if(platforms.size() == 1)
	{
		chosen_platform_index = 0;
	}
	else
	{
		fcppt::io::cout << FCPPT_TEXT("Your choice: ");
		do
			chosen_platform_index =
				query_value_from_user<sge::opencl::platform::object_sequence::size_type>(
					fcppt::io::cin);
		while(chosen_platform_index >= platforms.size());
	}

	fcppt::io::cout << FCPPT_TEXT("List devices with properties? [y/n] ");

	fcppt::char_type list_devices;
	do
		list_devices =
			query_value_from_user<fcppt::char_type>(
				fcppt::io::cin);
	while(list_devices != FCPPT_TEXT('y') && list_devices != FCPPT_TEXT('n'));

	sge::opencl::platform::object &chosen_platform =
		platforms[chosen_platform_index];

	if(list_devices == FCPPT_TEXT('y'))
	{
		fcppt::io::cout
			<< FCPPT_TEXT("Number of devices on this platform: ")
			<< chosen_platform.devices().size()
			<< FCPPT_TEXT("\n");
		fcppt::io::cout << FCPPT_TEXT("Device listing begin:\n");
		fcppt::io::cout << FCPPT_TEXT("-----------------------\n");

		for(
			sge::opencl::device::object_sequence::const_iterator current_device =
				chosen_platform.devices().begin();
			current_device != chosen_platform.devices().end();
			++current_device)
		{
			current_device->output_info(
				std::cout);
			fcppt::io::cout << FCPPT_TEXT("-----------------------\n");
		}

		fcppt::io::cout << FCPPT_TEXT("-----------------------\n");
		fcppt::io::cout << FCPPT_TEXT("Device listing end\n");
	}

	fcppt::io::cout << FCPPT_TEXT("Creating a context with all devices on this platform...");

	sge::opencl::device::object_ref_sequence device_refs;
	for(
		sge::opencl::device::object_sequence::iterator current_device =
			chosen_platform.devices().begin();
		current_device != chosen_platform.devices().end();
		++current_device)
		device_refs.push_back(
			&(*current_device));


	sge::opencl::context::object main_context(
		sge::opencl::context::parameters(
			chosen_platform,
			device_refs));

	
#if 0


	typedef
	fcppt::container::raw_vector<cl_platform_id>
	platform_id_sequence;

	platform_id_sequence platform_ids(
		static_cast<platform_id_sequence::size_type>(
			number_of_platforms));

	fcppt::io::cout << FCPPT_TEXT("Querying platform's information...\n");

  // First, query the total number of platforms
  error_code =
		clGetPlatformIDs(
			number_of_platforms,
			platform_ids.data(),
			// pointer to the number of platforms
			0);

	sge::examples::opencl::handle_error(
		error_code,
		FCPPT_TEXT("clGetplatformIDs"));

	fcppt::io::cout << FCPPT_TEXT("Done...\n");

	fcppt::io::cout << FCPPT_TEXT("Choose your desired platform: \n");
	platform_id_sequence::size_type platform_index = 0;
	for(
		platform_id_sequence::const_iterator platform_it =
			platform_ids.begin();
		platform_it != platform_ids.end();
		++platform_it)
	{
		std::cout << "-----------------------------------------\n";
		std::cout << "Platform " << platform_index++ << ":\n";
		std::cout << "-----------------------------------------\n";

		fcppt::container::array<std::string,5> properties_string =
			{{
				"CL_PLATFORM_PROFILE",
				"CL_PLATFORM_VERSION",
				"CL_PLATFORM_NAME",
				"CL_PLATFORM_VENDOR",
				"CL_PLATFORM_EXTENSIONS"
			}};

		fcppt::container::array<cl_platform_info,5> properties_value =
			{{
				CL_PLATFORM_PROFILE,
				CL_PLATFORM_VERSION,
				CL_PLATFORM_NAME,
				CL_PLATFORM_VENDOR,
				CL_PLATFORM_EXTENSIONS
			}};

		for(std::size_t i = 0; i < properties_value.size(); ++i)
			std::cout
				<< properties_string[i]
				<< ": "
				<<
					sge::examples::opencl::platform_info(
						*platform_it,
						properties_value[i])
				<<
					"\n";

		std::cout << "-----------------------------------------\n";
	}

	fcppt::io::cout << FCPPT_TEXT("Your choice: ");
	platform_id_sequence::size_type input_platform_index;
	while(!(fcppt::io::cin >> input_platform_index) || input_platform_index > platform_ids.size())
	{
		fcppt::io::cin.clear();
		fcppt::io::cin.ignore(
			std::numeric_limits<std::streamsize>::max(),
			FCPPT_TEXT('\n'));
	}

	std::cout << "-----------------------------------------\n";

	cl_platform_id const &chosen_platform =
		platform_ids[
			input_platform_index];

	std::cout << "Querying the number of devices on that platform...\n";

	cl_uint number_of_devices;

	error_code =
		clGetDeviceIDs(
			chosen_platform,
			CL_DEVICE_TYPE_ALL,
			// Number of entries
			0,
			// Device data
			0,
			&number_of_devices);

	FCPPT_ASSERT_PRE(
		number_of_devices);

	sge::examples::opencl::handle_error(
		error_code,
		FCPPT_TEXT("clGetDeviceIDs"));

	std::cout << "Done...\n";

	typedef
	fcppt::container::raw_vector<cl_device_id>
	device_id_sequence;

	device_id_sequence device_ids(
		static_cast<device_id_sequence::size_type>(
			number_of_devices));

	error_code =
		clGetDeviceIDs(
			chosen_platform,
			CL_DEVICE_TYPE_ALL,
			// Number of entries
			number_of_devices,
			// Device data
			device_ids.data(),
			// Pointer to the number of devices
			0);

	sge::examples::opencl::handle_error(
		error_code,
		FCPPT_TEXT("clGetDeviceIDs"));

	fcppt::io::cout << FCPPT_TEXT("Choose your desired device(s): \n");
	device_id_sequence::size_type device_index = 0;

	for(
		device_id_sequence::const_iterator device_it =
			device_ids.begin();
		device_it != device_ids.end();
		++device_it)
	{
		std::cout << "-----------------------------------------\n";
		std::cout << "Device " << device_index++ << ":\n";
		std::cout << "-----------------------------------------\n";

	}

	fcppt::io::cout << FCPPT_TEXT("Your choice: ");
	device_id_sequence::size_type input_device_index;
	while(!(fcppt::io::cin >> input_device_index) || input_device_index > device_ids.size())
	{
		fcppt::io::cin.clear();
		fcppt::io::cin.ignore(
			std::numeric_limits<std::streamsize>::max(),
			FCPPT_TEXT('\n'));
	}

#endif
}
catch(fcppt::exception const &e)
{
	fcppt::io::cerr << FCPPT_TEXT("fcppt::exception caught: ") << e.string() << FCPPT_TEXT("\n");
	return EXIT_FAILURE;
}
catch (std::exception const &e)
{
	std::cerr << "std::exception caught: " << e.what() << "\n";
	return EXIT_FAILURE;
}
