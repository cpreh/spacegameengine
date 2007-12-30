#include <boost/bind.hpp>
#include "../stdlib.hpp"

sge::con::stdlib::stdlib(const callback_type &print)
	: print(print) 
{
	add(L"set",boost::bind(&stdlib::set,this,_1));
	add(L"get",boost::bind(&stdlib::set,this,_1));
	add(L"listvars",boost::bind(&stdlib::listvars,this,_1));
	add(L"listfuncs",boost::bind(&stdlib::listfuncs,this,_1));
}

void sge::con::stdlib::get(const arg_list &args)
{
	if (args.size() < 2)
	{
		print(L"error: no variable given, use "+sge::string(1,prefix())+args[0]+L" <variable name>");
		return;
	}

	try
	{
		print(args[1]+L"=\""+get_var(args[1])+L"\"");
	}
	catch (const exception &e)
	{
		print(L"error: "+e.wide_what());
	}
}

void sge::con::stdlib::set(const arg_list &args)
{
	if (args.size() < 3)
	{
		print(L"error: no variable or value given, use "+sge::string(1,prefix())+args[0]+L" <variable name> <value>");
		return;
	}

	try
	{
		set_var(args[1],args[2]);
		print(args[1]+L"=\""+get_var(args[1])+L"\"");
	}
	catch (const exception &e)
	{
		print(L"error: "+e.wide_what());
	}
}

void sge::con::stdlib::listvars(const arg_list &args)
{
	string search_string;
	if (args.size() > 1)
		search_string = args[1];

	print(L"------------variables begin------------");
	const var_map &v = vars();
	for (var_map::const_iterator i = v.begin(); i != v.end(); ++i)
	{
		if (i->first.find(search_string) != string::npos)
			print(i->first+L"=\""+i->second->get()+L"\"");
	}
	print(L"------------variables end--------------");
}

void sge::con::stdlib::listfuncs(const arg_list &args)
{
	string search_string;
	if (args.size() > 1)
		search_string = args[1];

	print(L"------------functions begin------------");
	const callback_map &f = funcs();
	for (callback_map::const_iterator i = f.begin(); i != f.end(); ++i)
		if (i->first.find(search_string) != string::npos)
			print(i->first);
	print(L"------------functions end--------------");
}
