#include "Includes.h"

#define INRANGE(x,a,b)    (x >= a && x <= b)
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))

template <typename T>
T cHookManager::Hook( void* pOriginal, void* pNew, int iIndex )
{
	if ( pOriginal == nullptr || pNew == nullptr )
		return nullptr;

	DWORD pBackupProtection;
	auto pOriginalVirtual = *static_cast< DWORD* >( pOriginal ) + 4 * iIndex;
	auto pBackupFunc = reinterpret_cast< void* >( *reinterpret_cast< DWORD* >( pOriginalVirtual ) );

	VirtualProtect( reinterpret_cast< void* >( pOriginalVirtual ), 4, 0x40, &pBackupProtection );
	*reinterpret_cast< DWORD* >( pOriginalVirtual ) = reinterpret_cast< DWORD >( pNew );
	VirtualProtect( reinterpret_cast< void* >( pOriginalVirtual ), 4, pBackupProtection, &pBackupProtection );

	return static_cast< T >( pBackupFunc );
}

MODULEINFO cHookManager::getModuleInfo( char* szModule )
{

	MODULEINFO modinfo = { nullptr };
	auto hModule = GetModuleHandleA( szModule );
	if ( hModule == nullptr )
		return modinfo;

	K32GetModuleInformation( GetCurrentProcess( ), hModule, &modinfo, sizeof( MODULEINFO ) );
	return modinfo;
}

DWORD cHookManager::findPattern( DWORD dwAddress, DWORD dwLength, const char* szPattern )
{
	if ( !dwAddress || !dwLength || !szPattern )
		return 0;

	auto pPattern = szPattern;
	DWORD dwMatchData = 0;
	DWORD dwReturn = 0;

	for ( auto pDataPatch = dwAddress; pDataPatch < dwLength; pDataPatch++ )
	{
		if ( !*pPattern )
			dwReturn = dwMatchData;

		if ( *PBYTE( pPattern ) == '\?' || *reinterpret_cast< BYTE* >( pDataPatch ) == ( ( pPattern[ 0 ] >= '0' && pPattern[ 0 ] <= '9' ? pPattern[ 0 ] - '0' : ( pPattern[ 0 ] & ~32 ) - 'A' + 10 ) << 4 | ( pPattern[ 1 ] >= '0' && pPattern[ 1 ] <= '9' ? pPattern[ 1 ] - '0' : ( pPattern[ 1 ] & ~32 ) - 'A' + 10 ) ) )
		{
			if ( !dwMatchData )
				dwMatchData = pDataPatch;

			if ( !pPattern[ 2 ] )
				dwReturn = dwMatchData;

			pPattern += *PWORD( pPattern ) == 16191 || *PBYTE( pPattern ) != '\?' ? 3 : 2;
		}
		else
		{
			pPattern = szPattern;
			dwMatchData = 0;
		}
	}

	return dwReturn;
}

DWORD cHookManager::getSignature( const char* szModuleName, const char* szPattern )
{
	auto pBase = reinterpret_cast< DWORD >( GetModuleHandleA( szModuleName ) );
	auto pDataHeader = reinterpret_cast< PIMAGE_NT_HEADERS >( pBase + reinterpret_cast< PIMAGE_DOS_HEADER >( pBase )->e_lfanew )->OptionalHeader;

	return findPattern( pBase + pDataHeader.BaseOfCode, pBase + pDataHeader.SizeOfCode, szPattern );
}