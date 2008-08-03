#include <sge/console/stdlib.hpp>
#include <sge/console/console.hpp>
#include <sge/console/var_base.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <boost/bind.hpp>

sge::con::stdlib::stdlib(const callback_type &print)
	: print(print) 
{
	add(SGE_TEXT("set"),boost::bind(&stdlib::set,this,_1));
	add(SGE_TEXT("get"),boost::bind(&stdlib::get,this,_1));
	add(SGE_TEXT("listvars"),boost::bind(&stdlib::listvars,this,_1));
	add(SGE_TEXT("listfuncs"),boost::bind(&stdlib::listfuncs,this,_1));
	add(SGE_TEXT("latch"),boost::bind(&stdlib::latch,this,_1));
	add(SGE_TEXT("help"),boost::bind(&stdlib::help,this,_1));
}

void sge::con::stdlib::help(const arg_list &)
{
	print(SGE_TEXT("use /get <var name> to get the current value of a variable"));
	print(SGE_TEXT("use /set <var name> <value> to set a variable"));
	print(SGE_TEXT("use /listvars got get a list of available vars"));
	print(SGE_TEXT("use /listfuncs to get a list of functions"));
}

void sge::con::stdlib::get(const arg_list &args)
{
	if (args.size() < 2)
	{
		print(SGE_TEXT("error: no variable given, use ")+sge::string(1,prefix())+args[0]+SGE_TEXT(" <variable name>"));
		return;
	}

	try
	{
		print(args[1]+SGE_TEXT("=\"")+get_var(args[1])+SGE_TEXT("\""));
	}
	catch (const exception &e)
	{
		print(SGE_TEXT("error: ")+e.what());
	}
}

void sge::con::stdlib::set(const arg_list &args)
{
	if (args.size() < 3)
	{
		print(SGE_TEXT("error: no variable or value given, use ")+sge::string(1,prefix())+args[0]+SGE_TEXT(" <variable name> <value>"));
		return;
	}

	try
	{
		set_var(args[1],args[2]);
		print(args[1]+SGE_TEXT("=\"")+get_var(args[1])+SGE_TEXT("\""));
	}
	catch (const exception &e)
	{
		print(SGE_TEXT("error: ")+e.what());
	}
}

void sge::con::stdlib::listvars(const arg_list &args)
{
	string search_string;
	if (args.size() > 1)
		search_string = args[1];

	print(SGE_TEXT("------------variables begin------------"));
	const var_map &v = vars();
	for (var_map::const_iterator i = v.begin(); i != v.end(); ++i)
	{
		if (i->first.find(search_string) != string::npos)
			print(i->first+SGE_TEXT("=\"")+i->second->get()+SGE_TEXT("\""));
	}
	print(SGE_TEXT("------------variables end--------------"));
}

void sge::con::stdlib::listfuncs(const arg_list &args)
{
	string search_string;
	if (args.size() > 1)
		search_string = args[1];

	print(SGE_TEXT("------------functions begin------------"));
	const callback_map &f = funcs();
	for (callback_map::const_iterator i = f.begin(); i != f.end(); ++i)
		if (i->first.find(search_string) != string::npos)
			print(i->first);
	print(SGE_TEXT("------------functions end--------------"));
}

void sge::con::stdlib::latch(const arg_list &args)
{
	if (args.size() < 2)
	{
		print(SGE_TEXT("error: syntax: ")+sge::string(1,prefix())+args[0]+SGE_TEXT(" <variable name> <value>"));
		return;
	}

	sge::con::latch(args[1],args[2]);
	print(SGE_TEXT("latched \"")+args[1]+SGE_TEXT("\" to \"")+args[2]+SGE_TEXT("\")"));
}
