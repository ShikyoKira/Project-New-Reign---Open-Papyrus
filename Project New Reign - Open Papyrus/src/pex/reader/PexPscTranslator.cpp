#include "PexPscTranslator.h"
#include <boost\algorithm\string.hpp>
#include <boost\algorithm\string_regex.hpp>
#include <QtCore\QCoreApplication>
#include <QtNetwork\QHostInfo>

using namespace std;

PexFile PPTranslation(vecstr storelines, string source)
{
	QString user = qgetenv("USER");
	QString machine = QHostInfo::localHostName();

	if (user.isEmpty()) user = qgetenv("USERNAME");		

	PexFile file(source, user.toStdString(), machine.toStdString());

	// string table
	tableRef.push_back(source.substr(source.rfind(".")));		// Source file name
	tableRef.push_back("");										// Empty string
	tableRef.push_back("GetState");								// GetState
	tableRef.push_back("GotoState");							// GotoState

	// Get Function Name
	for (auto& line  : storelines)
	{
		string lower = boost::to_lower_copy(line);
		boost::smatch match;

		if (boost::regex_search(lower, match, boost::regex("^(?>((?>bool|int|float|string)) |)function ([\\w]+)\\(\\)(?> (global)|)( native)?")))
		{
			if (match.str(2).length() > 0)
			{
				tableRef.push_back(line.substr(match.position(2), match.str(2).length()));
			}
		}
	}

	tableRef.push_back("onBeginState");
	tableRef.push_back("onEndState");

	// debug info




	return file;
}


