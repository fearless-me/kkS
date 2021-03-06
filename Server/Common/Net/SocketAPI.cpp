//#include "stdafx.h"
//////////////////////////////////////////////////////////////////////
//
// SocketAPI.cpp
//
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////

//#include "FileAPI.h"
#include "SocketAPI.h"

#if __WINDOWS__
#elif __LINUX__
#include <sys/types.h>			// for accept()
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>			// for inet_xxx()
#include <netinet/in.h>
#include <errno.h>				// for errno
#endif


//////////////////////////////////////////////////
// external variable
//////////////////////////////////////////////////
#if __LINUX__
extern int32_t errno;
#endif

CHAR Error[_ESIZE] ;
//////////////////////////////////////////////////////////////////////
//
// SOCKET SocketAPI::socket_ex ( INT domain , INT type , INT protocol ) 
//
// exception version of socket()
//
// Parameters
//     domain - AF_INET(internet socket), AF_UNIX(internal socket), ...
//	   type  - SOCK_STREAM(TCP), SOCK_DGRAM(UDP), ...
//     protocol - 0
//
// Return 
//     socket descriptor
//
//
//////////////////////////////////////////////////////////////////////
SOCKET SocketAPI::socket_ex ( int32_t domain , int32_t type , int32_t protocol ) 
{
	SOCKET s = ::socket(domain,type,protocol);

	if ( s == INVALID_SOCKET ) 
	{
#if __LINUX__
		switch ( errno ) 
		{
		case EPROTONOSUPPORT :
		case EMFILE : 
		case ENFILE : 
		case EACCES : 
		case ENOBUFS : 
		default : 
			{
				break;
			}
		}//end of switch
#elif __WINDOWS__
		int32_t iErr = WSAGetLastError() ;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( Error, "WSANOTINITIALISED", _ESIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
			break ;
		case WSAEAFNOSUPPORT : 
			strncpy( Error, "WSAEAFNOSUPPORT", _ESIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
			break ;
		case WSAEMFILE : 
			strncpy( Error, "WSAEMFILE", _ESIZE ) ;
			break ;
		case WSAENOBUFS : 
			strncpy( Error, "WSAENOBUFS", _ESIZE ) ;
			break ;
		case WSAEPROTONOSUPPORT : 
			strncpy( Error, "WSAEPROTONOSUPPORT", _ESIZE ) ;
			break ;
		case WSAEPROTOTYPE : 
			strncpy( Error, "WSAEPROTOTYPE", _ESIZE ) ;
			break ;
		case WSAESOCKTNOSUPPORT : 
			strncpy( Error, "WSAESOCKTNOSUPPORT", _ESIZE ) ;
			break ;
		default : 
			{
				strncpy( Error, "UNKNOWN", _ESIZE ) ;
				break ;
			};
		};//end of switch
#endif
	}

	return s;
}


//////////////////////////////////////////////////////////////////////
//
// void SocketAPI::bind_ex ( SOCKET s , const struct sockaddr * addr , uint32_t addrlen ) 
//
// exception version of bind()
//
// Parameters
//     s       - socket descriptor 
//     addr    - socket address structure ( normally struct sockaddr_in )
//     addrlen - length of socket address structure
//
// Return
//     none
//
//
//////////////////////////////////////////////////////////////////////
bool SocketAPI::bind_ex ( SOCKET s , const struct sockaddr * addr , uint32_t addrlen ) 
{
	if ( bind ( s , addr , addrlen ) == SOCKET_ERROR ) 
	{
#if __LINUX__
		switch ( errno ) 
		{
		case EADDRINUSE :
		case EINVAL : 
		case EACCES : 
		case ENOTSOCK : 
		case EBADF : 
		case EROFS : 
		case EFAULT : 
		case ENAMETOOLONG : 
		case ENOENT : 
		case ENOMEM : 
		case ENOTDIR : 
		case ELOOP : 
		default :
			{
				break;
			}
		}//end of switch
#elif __WINDOWS__
		int32_t iErr = WSAGetLastError() ;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( Error, "WSAESOCKTNOSUPPORT", _ESIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
			break ;
		case WSAEADDRINUSE : 
			strncpy( Error, "WSAEADDRINUSE", _ESIZE ) ;
			break ;
		case WSAEADDRNOTAVAIL : 
			strncpy( Error, "WSAEADDRNOTAVAIL", _ESIZE ) ;
			break ;
		case WSAEFAULT : 
			strncpy( Error, "WSAEFAULT", _ESIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
			break ;
		case WSAEINVAL : 
			strncpy( Error, "WSAEINVAL", _ESIZE ) ;
			break ;
		case WSAENOBUFS : 
			strncpy( Error, "WSAENOBUFS", _ESIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( Error, "WSAENOTSOCK", _ESIZE ) ;
			break ;
		default :
			{
				strncpy( Error, "UNKNOWN", _ESIZE ) ;
				break ;
			};
		};//end of switch
#endif

		return false ;
	}

	return true ;
}


//////////////////////////////////////////////////////////////////////
//
// void SocketAPI::connect_ex ( SOCKET s , const struct sockaddr * addr , uint32_t addrlen )
//
// exception version of connect() system call
//
// Parameters
//     s       - socket descriptor
//     addr    - socket address structure
//     addrlen - length of socket address structure
//
// Return
//     none
//
//////////////////////////////////////////////////////////////////////
bool SocketAPI::connect_ex ( SOCKET s , const struct sockaddr * addr , uint32_t addrlen )
{
	if ( connect(s,addr,addrlen) == SOCKET_ERROR ) 
	{
#if __LINUX__
		switch ( errno ) {
		case EALREADY : 
		case EINPROGRESS : 
		case ECONNREFUSED : 
		case EISCONN : 
		case ETIMEDOUT : 
		case ENETUNREACH : 
		case EADDRINUSE : 
		case EBADF : 
		case EFAULT : 
		case ENOTSOCK : 
		default :
			{
				break;
			}
		}//end of switch
#elif __WINDOWS__
		int32_t iErr = WSAGetLastError() ;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( Error, "WSANOTINITIALISED", _ESIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
			break ;
		case WSAEADDRINUSE : 
			strncpy( Error, "WSAEADDRINUSE", _ESIZE ) ;
			break ;
		case WSAEINTR : 
			strncpy( Error, "WSAEINTR", _ESIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
			break ;
		case WSAEALREADY : 
			strncpy( Error, "WSAEALREADY", _ESIZE ) ;
			break ;
		case WSAEADDRNOTAVAIL : 
			strncpy( Error, "WSAEADDRNOTAVAIL", _ESIZE ) ;
			break ;
		case WSAEAFNOSUPPORT : 
			strncpy( Error, "WSAEAFNOSUPPORT", _ESIZE ) ;
			break ;
		case WSAECONNREFUSED : 
			strncpy( Error, "WSAECONNREFUSED", _ESIZE ) ;
			break ;
		case WSAEFAULT : 
			strncpy( Error, "WSAEFAULT", _ESIZE ) ;
			break ;
		case WSAEINVAL : 
			strncpy( Error, "WSAEINVAL", _ESIZE ) ;
			break ;
		case WSAEISCONN : 
			strncpy( Error, "WSAEISCONN", _ESIZE ) ;
			break ;
		case WSAENETUNREACH : 
			strncpy( Error, "WSAENETUNREACH", _ESIZE ) ;
			break ;
		case WSAENOBUFS : 
			strncpy( Error, "WSAENOBUFS", _ESIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( Error, "WSAENOTSOCK", _ESIZE ) ;
			break ;
		case WSAETIMEDOUT : 
			strncpy( Error, "WSAETIMEDOUT", _ESIZE ) ;
			break ;
		case WSAEWOULDBLOCK  : 
			strncpy( Error, "WSAEWOULDBLOCK", _ESIZE ) ;
			break ;
		default :
			{
				strncpy( Error, "UNKNOWN", _ESIZE ) ;
				break ;
			};
		};//end of switch
#endif
		return false ;
	}

	return true ;
}


//////////////////////////////////////////////////////////////////////
//
// void SocketAPI::listen_ex ( SOCKET s , uint32_t backlog )
//
// exception version of listen()
//
// Parameters
//     s       - socket descriptor
//     backlog - waiting queue length
//
// Return
//     none
//
//
//////////////////////////////////////////////////////////////////////
bool SocketAPI::listen_ex ( SOCKET s , uint32_t backlog ) 
{
	if ( listen( s , backlog ) == SOCKET_ERROR ) 
	{
#if __LINUX__
		switch ( errno ) 
		{
		case EBADF : 
		case ENOTSOCK :
		case EOPNOTSUPP :
		default :
			{
				break;
			}
		}//end of switch
#elif __WINDOWS__
		int32_t iErr = WSAGetLastError() ;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( Error, "WSANOTINITIALISED", _ESIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
			break ;
		case WSAEADDRINUSE : 
			strncpy( Error, "WSAEADDRINUSE", _ESIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
			break ;
		case WSAEINVAL : 
			strncpy( Error, "WSAEINVAL", _ESIZE ) ;
			break ;
		case WSAEISCONN : 
			strncpy( Error, "WSAEISCONN", _ESIZE ) ;
			break ;
		case WSAEMFILE : 
			strncpy( Error, "WSAEMFILE", _ESIZE ) ;
			break ;
		case WSAENOBUFS : 
			strncpy( Error, "WSAENOBUFS", _ESIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( Error, "WSAENOTSOCK", _ESIZE ) ;
			break ;
		case WSAEOPNOTSUPP : 
			strncpy( Error, "WSAEOPNOTSUPP", _ESIZE ) ;
			break ;
		default :
			{
				strncpy( Error, "UNKNOWN", _ESIZE ) ;
				break ;
			};
		};//end of switch
#endif

		return false ;
	}

	return true ;
}


//////////////////////////////////////////////////////////////////////
//
//SOCKET SocketAPI::accept_ex ( SOCKET s , struct sockaddr * addr , uint32_t * addrlen ) 
//
// exception version of accept()
//
// Parameters
//     s       - socket descriptor
//     addr    - socket address structure
//     addrlen - length of socket address structure
//
// Return
//     none
//
//
//////////////////////////////////////////////////////////////////////
SOCKET SocketAPI::accept_ex ( SOCKET s , struct sockaddr * addr , uint32_t * addrlen )
{
#if __LINUX__
	SOCKET client = accept( s , addr , addrlen );
#elif __WINDOWS__
	SOCKET client = accept( s , addr , (int*)addrlen );
#endif

	if ( client == INVALID_SOCKET ) 
	{
#if __LINUX__
		switch ( errno ) 
		{

		case EWOULDBLOCK : 

		case ECONNRESET :
		case ECONNABORTED :
		case EPROTO :
		case EINTR :
			// from UNIX Network Programming 2nd, 15.6
			// with nonblocking-socket, ignore above errors

		case EBADF : 
		case ENOTSOCK : 
		case EOPNOTSUPP : 
		case EFAULT : 

		default :
			{
				break;
			}
		}//end of switch
#elif __WINDOWS__
		int32_t iErr = WSAGetLastError() ;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( Error, "WSANOTINITIALISED", _ESIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
			break ;
		case WSAEFAULT : 
			strncpy( Error, "WSAEFAULT", _ESIZE ) ;
			break ;
		case WSAEINTR : 
			strncpy( Error, "WSAEINTR", _ESIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
			break ;
		case WSAEINVAL : 
			strncpy( Error, "WSAEINVAL", _ESIZE ) ;
			break ;
		case WSAEMFILE : 
			strncpy( Error, "WSAEMFILE", _ESIZE ) ;
			break ;
		case WSAENOBUFS : 
			strncpy( Error, "WSAENOBUFS", _ESIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( Error, "WSAENOTSOCK", _ESIZE ) ;
			break ;
		case WSAEOPNOTSUPP : 
			strncpy( Error, "WSAEOPNOTSUPP", _ESIZE ) ;
			break ;
		case WSAEWOULDBLOCK : 
			strncpy( Error, "WSAEWOULDBLOCK", _ESIZE ) ;
			break ;
		default :
			{
				strncpy( Error, "UNKNOWN", _ESIZE ) ;
				break ;
			};
		};//end of switch
#endif
	} else {
	}

	return client;
}


//////////////////////////////////////////////////////////////////////
//
// void SocketAPI::getsockopt_ex ( SOCKET s , INT level , INT optname , void * optval , uint32_t * optlen )
//
// exception version of getsockopt()
//
// Parameters
//     s       - socket descriptor
//     level   - socket option level ( SOL_SOCKET , ... )
//     optname - socket option name ( SO_REUSEADDR , SO_LINGER , ... )
//     optval  - pointer to contain option value
//     optlen  - length of optval
//
// Return
//     none
//
//
//////////////////////////////////////////////////////////////////////
bool SocketAPI::getsockopt_ex ( SOCKET s , int32_t level , int32_t optname , void * optval , uint32_t * optlen )
{
#if __LINUX__
	if ( getsockopt( s , level , optname , optval , optlen ) == SOCKET_ERROR ) 
	{
		switch ( errno ) 
		{
		case EBADF : 
		case ENOTSOCK : 
		case ENOPROTOOPT : 
		case EFAULT : 
		default :
			{
				break;
			}
		}//end of switch

		return false ;
	}
#elif __WINDOWS__
	if ( getsockopt( s , level , optname , (CHAR*)optval , (int*)optlen ) == SOCKET_ERROR ) 
	{
		int32_t iErr = WSAGetLastError() ;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( Error, "WSANOTINITIALISED", _ESIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
			break ;
		case WSAEFAULT : 
			strncpy( Error, "WSAEFAULT", _ESIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
			break ;
		case WSAEINVAL : 
			strncpy( Error, "WSAEINVAL", _ESIZE ) ;
			break ;
		case WSAENOPROTOOPT : 
			strncpy( Error, "WSAENOPROTOOPT", _ESIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( Error, "WSAENOTSOCK", _ESIZE ) ;
			break ;
		default : 
			{
				strncpy( Error, "UNKNOWN", _ESIZE ) ;
				break ;
			};
		};//end of switch

		return false ;
	}
#endif

	return true ;
}

uint32_t SocketAPI::getsockopt_ex2 ( SOCKET s , int32_t level , int32_t optname , void * optval , uint32_t * optlen )
{
#if __LINUX__
	if ( getsockopt( s , level , optname , optval , optlen ) == SOCKET_ERROR ) 
	{
		switch ( errno ) 
		{
		case EBADF : 
			return 1;
		case ENOTSOCK : 
			return 2;
		case ENOPROTOOPT : 
			return 3;
		case EFAULT : 
			return 4;
		default :
			return 5;
		}//end of switch
	}
	return 0;

#elif __WINDOWS__
	if ( getsockopt( s , level , optname , (CHAR*)optval , (int*)optlen ) == SOCKET_ERROR ) 
	{
		int32_t iErr = WSAGetLastError() ;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED:
			strncpy( Error, "WSANOTINITIALISED", _ESIZE ) ;
			break ;
		case WSAENETDOWN:
			strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
			break ;
		case WSAEFAULT:
			strncpy( Error, "WSAEFAULT", _ESIZE ) ;
			break ;
		case WSAEINPROGRESS:
			strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
			break ;
		case WSAEINVAL:
			strncpy( Error, "WSAEINVAL", _ESIZE ) ;
			break ;
		case WSAENOPROTOOPT:
			strncpy( Error, "WSAENOPROTOOPT", _ESIZE ) ;
			break ;
		case WSAENOTSOCK:
			strncpy( Error, "WSAENOTSOCK", _ESIZE ) ;
			break ;
		default : 
			{
				strncpy( Error, "UNKNOWN", _ESIZE ) ;
				break ;
			};
		}
	}
#endif

	return 0;
}

//////////////////////////////////////////////////////////////////////
//
// void SocketAPI::setsockopt_ex ( SOCKET s , INT level , INT optname , const void * optval , uint32_t optlen )
//
// exception version of setsockopt()
//
// Parameters
//     s       - socket descriptor
//     level   - socket option level ( SOL_SOCKET , ... )
//     optname - socket option name ( SO_REUSEADDR , SO_LINGER , ... )
//     optval  - pointer to contain option value
//     optlen  - length of optval
//
// Return
//     none
//
//
//////////////////////////////////////////////////////////////////////
bool SocketAPI::setsockopt_ex ( SOCKET s , int32_t level , int32_t optname , const void * optval , uint32_t optlen )
{
#if __LINUX__
	if ( setsockopt( s , level , optname , optval , optlen ) == SOCKET_ERROR ) 
	{
		switch ( errno ) 
		{
		case EBADF : 
		case ENOTSOCK : 
		case ENOPROTOOPT : 
		case EFAULT : 
		default :
			{
				break;
			}
		}//end of switch

		return false ;
	}
#elif __WINDOWS__
	if ( setsockopt( s , level , optname , (CHAR*)optval , optlen ) == SOCKET_ERROR ) 
	{
		int32_t iErr = WSAGetLastError() ;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( Error, "WSANOTINITIALISED", _ESIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
			break ;
		case WSAEFAULT : 
			strncpy( Error, "WSAEFAULT", _ESIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
			break ;
		case WSAEINVAL : 
			strncpy( Error, "WSAEINVAL", _ESIZE ) ;
			break ;
		case WSAENETRESET : 
			strncpy( Error, "WSAENETRESET", _ESIZE ) ;
			break ;
		case WSAENOPROTOOPT : 
			strncpy( Error, "WSAENOPROTOOPT", _ESIZE ) ;
			break ;
		case WSAENOTCONN : 
			strncpy( Error, "WSAENOTCONN", _ESIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( Error, "WSAENOTSOCK", _ESIZE ) ;
			break ;
		default :
			{
				strncpy( Error, "UNKNOWN", _ESIZE ) ;
				break ;
			};
		};//end of switch

		return false ;
	}
#endif

	return true ;
}


//////////////////////////////////////////////////////////////////////
//
// uint32_t SocketAPI::send_ex ( SOCKET s , const void * buf , uint32_t len , uint32_t flags )
// 
// exception version of send()
// 
// Parameters 
//     s     - socket descriptor
//     buf   - input buffer
//     len   - input data length
//     flags - send flag (MSG_OOB,MSG_DONTROUTE)
// 
// Return 
//     length of bytes sent
// 
// 
//////////////////////////////////////////////////////////////////////
uint32_t SocketAPI::send_ex ( SOCKET s , const void * buf , uint32_t len , uint32_t flags )
{
	int32_t nSent = 0;

	_MY_TRY
	{

#if __LINUX__
		nSent = send(s,buf,len,flags);
#elif __WINDOWS__
		nSent = send(s,(const CHAR *)buf,len,flags);
#endif

		if ( nSent == SOCKET_ERROR ) 
		{
#if __LINUX__
			switch ( errno ) 
			{

			case EWOULDBLOCK : 
				return SOCKET_ERROR_WOULDBLOCK;

			case ECONNRESET :
			case EPIPE :

			case EBADF : 
			case ENOTSOCK : 
			case EFAULT : 
			case EMSGSIZE : 
			case ENOBUFS : 

			default : 
				{
					break;
				}
			}//end of switch
#elif __WINDOWS__
			int32_t iErr = WSAGetLastError() ;
			switch ( iErr ) 
			{
			case WSANOTINITIALISED : 
				strncpy( Error, "WSANOTINITIALISED", _ESIZE ) ;
				break ;
			case WSAENETDOWN : 
				strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
				break ;
			case WSAEACCES : 
				strncpy( Error, "WSAEACCES", _ESIZE ) ;
				break ;
			case WSAEINTR : 
				strncpy( Error, "WSAEINTR", _ESIZE ) ;
				break ;
			case WSAEINPROGRESS : 
				strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
				break ;
			case WSAEFAULT : 
				strncpy( Error, "WSAEFAULT", _ESIZE ) ;
				break ;
			case WSAENETRESET : 
				strncpy( Error, "WSAENETRESET", _ESIZE ) ;
				break ;
			case WSAENOBUFS : 
				strncpy( Error, "WSAENOBUFS", _ESIZE ) ;
				break ;
			case WSAENOTCONN : 
				strncpy( Error, "WSAENOTCONN", _ESIZE ) ;
				break ;
			case WSAENOTSOCK : 
				strncpy( Error, "WSAENOTSOCK", _ESIZE ) ;
				break ;
			case WSAEOPNOTSUPP : 
				strncpy( Error, "WSAEOPNOTSUPP", _ESIZE ) ;
				break ;
			case WSAESHUTDOWN : 
				strncpy( Error, "WSAESHUTDOWN", _ESIZE ) ;
				break ;
			case WSAEWOULDBLOCK : 
				//			strncpy( Error, "WSAEWOULDBLOCK", _ESIZE ) ;
				return SOCKET_ERROR_WOULDBLOCK ;
				break ;
			case WSAEMSGSIZE : 
				strncpy( Error, "WSAEMSGSIZE", _ESIZE ) ;
				break ;
			case WSAEHOSTUNREACH : 
				strncpy( Error, "WSAEHOSTUNREACH", _ESIZE ) ;
				break ;
			case WSAEINVAL : 
				strncpy( Error, "WSAEINVAL", _ESIZE ) ;
				break ;
			case WSAECONNABORTED : 
				strncpy( Error, "WSAECONNABORTED", _ESIZE ) ;
				break ;
			case WSAECONNRESET : 
				strncpy( Error, "WSAECONNRESET", _ESIZE ) ;
				break ;
			case WSAETIMEDOUT : 
				strncpy( Error, "WSAETIMEDOUT", _ESIZE ) ;
				break ;
			default :
				{
					strncpy( Error, "UNKNOWN", _ESIZE ) ;
					break ;
				};
			};//end of switch
#endif
		} 
		else if ( nSent == 0 )
		{
		}

	}
	_MY_CATCH
	{
	}

	return nSent;
}


//////////////////////////////////////////////////////////////////////
// exception version of sendto()
//////////////////////////////////////////////////////////////////////
uint32_t SocketAPI::sendto_ex ( SOCKET s , const void * buf , int32_t len , uint32_t flags , const struct sockaddr * to , int32_t tolen )
{
#if __LINUX__
	int32_t nSent = sendto(s,buf,len,flags,to,tolen);
#elif __WINDOWS__
	int32_t nSent = sendto(s,(const CHAR *)buf,len,flags,to,tolen);
#endif

	if ( nSent == SOCKET_ERROR ) 
	{
#if __LINUX__
		switch ( errno ) 
		{

		case EWOULDBLOCK : 
			return 0;

		case ECONNRESET :
		case EPIPE :

		case EBADF : 
		case ENOTSOCK : 
		case EFAULT : 
		case EMSGSIZE : 
		case ENOBUFS : 

		default : 
			{
				break;
			}
		}	
#elif __WINDOWS__
#endif
	}

	return nSent;
}


//////////////////////////////////////////////////////////////////////
//
// uint32_t SocketAPI::recv_ex ( SOCKET s , void * buf , uint32_t len , uint32_t flags )
//
// exception version of recv()
//
// Parameters 
//     s     - socket descriptor
//     buf   - input buffer
//     len   - input data length
//     flags - send flag (MSG_OOB,MSG_DONTROUTE)
// 
// Return 
//     length of bytes received
// 
//
//////////////////////////////////////////////////////////////////////
uint32_t SocketAPI::recv_ex ( SOCKET s , void * buf , uint32_t len , uint32_t flags )
{
#if __LINUX__
	int32_t nrecv = recv(s,buf,len,flags);
#elif __WINDOWS__
	int32_t nrecv = recv(s,(CHAR*)buf,len,flags);
#endif

	if ( nrecv == SOCKET_ERROR ) 
	{
#if __LINUX__
		switch ( errno ) 
		{

		case EWOULDBLOCK : 
			return SOCKET_ERROR_WOULDBLOCK;

		case ECONNRESET :
		case EPIPE :

		case EBADF : 
		case ENOTCONN : 
		case ENOTSOCK : 
		case EINTR : 
		case EFAULT : 

		default : 
			{
				break;
			}
		}//end of switch

#elif __WINDOWS__
		int32_t iErr = WSAGetLastError() ;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( Error, "WSANOTINITIALISED", _ESIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
			break ;
		case WSAEFAULT : 
			strncpy( Error, "WSAEFAULT", _ESIZE ) ;
			break ;
		case WSAENOTCONN : 
			strncpy( Error, "WSAENOTCONN", _ESIZE ) ;
			break ;
		case WSAEINTR : 
			strncpy( Error, "WSAEINTR", _ESIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
			break ;
		case WSAENETRESET : 
			strncpy( Error, "WSAENETRESET", _ESIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( Error, "WSAENOTSOCK", _ESIZE ) ;
			break ;
		case WSAEOPNOTSUPP : 
			strncpy( Error, "WSAEOPNOTSUPP", _ESIZE ) ;
			break ;
		case WSAESHUTDOWN : 
			strncpy( Error, "WSAESHUTDOWN", _ESIZE ) ;
			break ;
		case WSAEWOULDBLOCK : 
			//			strncpy( Error, "WSAEWOULDBLOCK", _ESIZE ) ;
			return SOCKET_ERROR_WOULDBLOCK ;
			break ;
		case WSAEMSGSIZE : 
			strncpy( Error, "WSAEMSGSIZE", _ESIZE ) ;
			break ;
		case WSAEINVAL : 
			strncpy( Error, "WSAEINVAL", _ESIZE ) ;
			break ;
		case WSAECONNABORTED : 
			strncpy( Error, "WSAECONNABORTED", _ESIZE ) ;
			break ;
		case WSAETIMEDOUT : 
			strncpy( Error, "WSAETIMEDOUT", _ESIZE ) ;
			break ;
		case WSAECONNRESET : 
			strncpy( Error, "WSAECONNRESET", _ESIZE ) ;
			break ;
		default :
			{
				strncpy( Error, "UNKNOWN", _ESIZE ) ;
				break ;
			};
		};//end of switch
#endif
	} 
	else if ( nrecv == 0 )
	{
	}

	return nrecv;
}


/////////////////////////////////////////////////////////////////////
// exception version of recvfrom()
/////////////////////////////////////////////////////////////////////
uint32_t SocketAPI::recvfrom_ex ( SOCKET s , void * buf , int32_t len , uint32_t flags , struct sockaddr * from , uint32_t * fromlen )
{
#if __LINUX__
	int32_t nReceived = recvfrom(s,buf,len,flags,from,fromlen);

#elif __WINDOWS__
	int32_t nReceived = recvfrom(s,(CHAR*)buf,len,flags,from,(int*)fromlen);
#endif

	if ( nReceived == SOCKET_ERROR ) 
	{
#if __LINUX__
		switch ( errno ) 
		{

		case EWOULDBLOCK : 
			return SOCKET_ERROR_WOULDBLOCK;

		case ECONNRESET :
		case EPIPE :

		case EBADF : 
		case ENOTCONN : 
		case ENOTSOCK : 
		case EINTR : 
		case EFAULT : 

		default : 
			{
				break;
			}
		}//end of switch
#elif __WINDOWS__
#endif
	}

	return nReceived;
}


/////////////////////////////////////////////////////////////////////
//
// void SocketAPI::closesocket_ex ( SOCKET s )
//
// exception version of closesocket()
//
// Parameters
//     s - socket descriptor
//
// Return
//     none
//
//
/////////////////////////////////////////////////////////////////////
bool SocketAPI::closesocket_ex ( SOCKET s )
{
#if __LINUX__
	close(s);
#elif __WINDOWS__
	if ( closesocket(s) == SOCKET_ERROR ) 
	{
		int32_t iErr = WSAGetLastError() ;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( Error, "WSANOTINITIALISED", _ESIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( Error, "WSAENOTSOCK", _ESIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
			break ;
		case WSAEINTR : 
			strncpy( Error, "WSAEINTR", _ESIZE ) ;
			break ;
		case WSAEWOULDBLOCK : 
			strncpy( Error, "WSAEWOULDBLOCK", _ESIZE ) ;
			break ;
		default : 
			{
				strncpy( Error, "UNKNOWN", _ESIZE ) ;
				break ;
			};
		};//end of switch

		return false ;
	}
#endif

	return true ;
}


/////////////////////////////////////////////////////////////////////
//
// void SocketAPI::ioctlsocket_ex ( SOCKET s , LONG cmd , ULONG * argp )
//
// exception version of ioctlsocket()
//
/////////////////////////////////////////////////////////////////////
bool SocketAPI::ioctlsocket_ex ( SOCKET s , LONG cmd , ULONG * argp )
{
#if __LINUX__
#elif __WINDOWS__
	if ( ioctlsocket(s,cmd,argp) == SOCKET_ERROR ) 
	{
		int32_t iErr = WSAGetLastError() ;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( Error, "WSANOTINITIALISED", _ESIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( Error, "WSAENOTSOCK", _ESIZE ) ;
			break ;
		case WSAEFAULT : 
			strncpy( Error, "WSAEFAULT", _ESIZE ) ;
			break ;
		default :
			{
				strncpy( Error, "UNKNOWN", _ESIZE ) ;
				break ;
			};
		};

		return false ;
	}
#endif

	return true ;
}


//////////////////////////////////////////////////////////////////////
//
// BOOL SocketAPI::getsocketnonblocking_ex ( SOCKET s ) 
//
// check if this socket is nonblocking mode
//
// Parameters
//     s - socket descriptor
//
// Return
//     TRUE if nonblocking, FALSE if blocking
//
//
//////////////////////////////////////////////////////////////////////
bool SocketAPI::getsocketnonblocking_ex ( SOCKET s )
{
#if __LINUX__
	int32_t flags = FileAPI::fcntl_ex( s , F_GETFL , 0 );

	return flags | O_NONBLOCK;
#elif __WINDOWS__
	return false ;
#endif
}


//////////////////////////////////////////////////////////////////////
//
// void SocketAPI::setsocketnonblocking_ex ( SOCKET s , BOOL on ) 
//
// make this socket blocking/nonblocking
//
// Parameters
//     s  - socket descriptor
//     on - TRUE if nonblocking, FALSE if blocking
//
// Return
//     none
//
//////////////////////////////////////////////////////////////////////
bool SocketAPI::setsocketnonblocking_ex ( SOCKET s , bool on )
{
#if __LINUX__
	int32_t flags = FileAPI::fcntl_ex( s , F_GETFL , 0 );

	if ( on )
		// make nonblocking fd
			flags |= O_NONBLOCK;
	else
		// make blocking fd
		flags &= ~O_NONBLOCK;

	FileAPI::fcntl_ex( s , F_SETFL , flags );

	return true;
#elif __WINDOWS__

	ULONG argp = ( on == true ) ? 1 : 0;
	return ioctlsocket_ex( s,FIONBIO,&argp);

#endif
}

//////////////////////////////////////////////////////////////////////
//
// uint32_t SocketAPI::availablesocket_ex ( SOCKET s )
//
// get amount of data in socket input buffer
//
// Parameters
//    s - socket descriptor
//
// Return
//    amount of data in socket input buffer
//
//
//////////////////////////////////////////////////////////////////////
uint32_t SocketAPI::availablesocket_ex ( SOCKET s )
{
#if __LINUX__
	return FileAPI::availablefile_ex(s);
#elif __WINDOWS__
	ULONG argp = 0;
	ioctlsocket_ex(s,FIONREAD,&argp);
	return argp;
#endif
}


//////////////////////////////////////////////////////////////////////
//
// void SocketAPI::shutdown_ex ( SOCKET s , uint32_t how )
//
// shutdown all or part of connection of socket
//
// Parameters
//     s   - socket descriptor
//     how - how to close ( all , send , receive )
//
// Return
//     none
//
//
//////////////////////////////////////////////////////////////////////
bool SocketAPI::shutdown_ex ( SOCKET s , uint32_t how )
{
	if ( shutdown(s,how) < 0 ) 
	{
#if __LINUX__
		switch ( errno ) {
		case EBADF : 
		case ENOTSOCK : 
		case ENOTCONN : 
		default : 
			{
				break;
			}
		}
#elif __WINDOWS__
		int32_t iErr = WSAGetLastError() ;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( Error, "WSANOTINITIALISED", _ESIZE ) ;
			break ;
		case WSAENETDOWN :
			strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
			break ;
		case WSAEINVAL : 
			strncpy( Error, "WSAEINVAL", _ESIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
			break ;
		case WSAENOTCONN : 
			strncpy( Error, "WSAENOTCONN", _ESIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( Error, "WSAENOTSOCK", _ESIZE ) ;
			break ;
		default :
			{
				strncpy( Error, "UNKNOWN", _ESIZE ) ;
				break ;
			};
		};
#endif

		return false ;
	}

	return true ;
}

//////////////////////////////////////////////////////////////////////
//
// INT SocketAPI::select_ex ( INT maxfdp1 , fd_set * readset , fd_set * writeset , fd_set * exceptset , struct timeval * timeout )
//
// system call for I/O multiplexing
//
// Parameters
//     maxfdp1   - 
//     readset   - 
//     writeset  - 
//     exceptset - 
//     timeout   - 
//
// Return
//     positive count of ready descriptors
//
//
//////////////////////////////////////////////////////////////////////
int32_t SocketAPI::select_ex ( int32_t maxfdp1 , fd_set * readset , fd_set * writeset , fd_set * exceptset , struct timeval * timeout )
{
	int32_t result = SOCKET_ERROR;

	_MY_TRY 
	{
		result = select( maxfdp1 , readset , writeset , exceptset , timeout );
		if( result == SOCKET_ERROR )
		{
#if __LINUX__

#elif __WINDOWS__
			int32_t iErr = WSAGetLastError() ;
			switch ( iErr ) 
			{
			case WSANOTINITIALISED : 
				strncpy( Error, "WSANOTINITIALISED", _ESIZE ) ;
				break ;
			case WSAEFAULT:
				strncpy( Error, "WSAEFAULT", _ESIZE ) ;
				break ;
			case WSAENETDOWN:
				strncpy( Error, "WSAENETDOWN", _ESIZE ) ;
				break ;
			case WSAEINVAL:
				strncpy( Error, "WSAEINVAL", _ESIZE ) ;
				break ;
			case WSAEINTR:
				strncpy( Error, "WSAEINTR", _ESIZE ) ;
				break ;
			case WSAEINPROGRESS:
				strncpy( Error, "WSAEINPROGRESS", _ESIZE ) ;
				break ;
			case WSAENOTSOCK:
				strncpy( Error, "WSAENOTSOCK", _ESIZE ) ;
				break ;
			default :
				{
					strncpy( Error, "UNKNOWN", _ESIZE ) ;
					break ;
				};
			};
#endif
		}//end if
	} 
	_MY_CATCH
	{
	}

	return result;
}




