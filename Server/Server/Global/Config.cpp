/************************************************************************/
/*                                                                      */
/************************************************************************/

#include "Config.h"

Config g_Config ;

Config::Config( )
{
__ENTER_FUNCTION


__LEAVE_FUNCTION
}

Config::~Config( )
{
__ENTER_FUNCTION


__LEAVE_FUNCTION
}

bool Config::Init(const CHAR* argv0)
{
__ENTER_FUNCTION_EX

	LoadLogConfig(argv0) ;

	return true ;

__LEAVE_FUNCTION_EX

	return false ;
}

void Config::ReLoad( )
{

}

void Config::LoadLogConfig(const CHAR* argv0)
{
__ENTER_FUNCTION
	//////////////////////////////////////////////////////////////////////////

	Assert(MakeDir("Runtime"));
	Assert(MakeDir("Runtime/Log"));
	
	//////////////////////////////////////////////////////////////////////////
	if( argv0 != NULL)
	{
		const char* slash = strrchr(argv0, '/');
#if defined(__WINDOWS__)
		if (!slash)  slash = strrchr(argv0, '\\');
#endif
		m_LogConfig.m_InvocationName = slash ? slash + 1 : argv0;
	}
	else
	{
		m_LogConfig.m_InvocationName = "UNKNOWN";
	}

	//////////////////////////////////////////////////////////////////////////
	HostName(m_LogConfig.m_HostName);

__LEAVE_FUNCTION
}


