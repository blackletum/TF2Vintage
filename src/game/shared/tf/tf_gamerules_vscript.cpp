//========= Copyright � Valve LLC, All rights reserved. =======================
//
// Purpose:		
//
// $NoKeywords: $
//=============================================================================
#include "cbase.h"
#include "filesystem.h"
#include "tf_gamerules.h"
#include "econ_item_system.h"
#include "tf_fx_shared.h"
#include "vscript_shared.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

#if defined( GAME_DLL )
class CScriptConvars : public CAutoGameSystem
{
public:
	void LevelInitPreEntity() OVERRIDE
	{
		m_AllowList.RemoveAll();

		KeyValuesAD kvAllowList( "vscript_convar_allowlist" );
		if ( kvAllowList->LoadFromFile( g_pFullFileSystem, "cfg/vscript_convar_allowlist.txt", "GAME" ) )
		{
			FOR_EACH_SUBKEY( kvAllowList, pSubKey )
			{
				if ( !V_stricmp( pSubKey->GetString(), "allowed" ) )
					m_AllowList.AddString( pSubKey->GetName() );
			}
		}
	}

	ScriptVariant_t GetClientConvarValue( int clientIndex, const char *name )
	{
		const char *cvar = engine->GetClientConVarValue( clientIndex, name );
		if ( cvar )
		{
			return ScriptVariant_t( cvar, true );
		}
		return SCRIPT_VARIANT_NULL;
	}

	ScriptVariant_t GetStr( const char *name )
	{
		ConVarRef cvar( name );
		if ( cvar.IsValid() )
		{
			return ScriptVariant_t( cvar.GetString(), true );
		}
		return SCRIPT_VARIANT_NULL;
	}

	ScriptVariant_t GetFloat( const char *name )
	{
		ConVarRef cvar( name );
		if ( cvar.IsValid() )
		{
			return ScriptVariant_t( cvar.GetFloat() );
		}
		return SCRIPT_VARIANT_NULL;
	}

	ScriptVariant_t GetInt( const char *name )
	{
		ConVarRef cvar( name );
		if ( cvar.IsValid() )
		{
			return ScriptVariant_t( cvar.GetInt() );
		}
		return SCRIPT_VARIANT_NULL;
	}

	ScriptVariant_t GetBool( const char *name )
	{
		ConVarRef cvar( name );
		if ( cvar.IsValid() )
		{
			return ScriptVariant_t( cvar.GetBool() );
		}
		return SCRIPT_VARIANT_NULL;
	}

	void SetValue( const char *name, ScriptVariant_t value )
	{
		ConVarRef cvar( name );
		if ( !cvar.IsValid() )
		{
			return;
		}

		switch ( value.m_type )
		{
			case FIELD_INTEGER:
			{
				cvar.SetValue( value.m_int );

				TFGameRules()->SaveConvar( cvar );
				break;
			}
			case FIELD_BOOLEAN:
			{
				cvar.SetValue( value.m_bool );

				TFGameRules()->SaveConvar( cvar );
				break;
			}
			case FIELD_FLOAT:
			{
				cvar.SetValue( value.m_float );

				TFGameRules()->SaveConvar( cvar );
				break;
			}
			case FIELD_CSTRING:
			{
				cvar.SetValue( value.m_pszString );

				TFGameRules()->SaveConvar( cvar );
				break;
			}
			default:
			{
				Warning( "%s.SetValue() unsupported value type %s\n", name, ScriptFieldTypeName( value.m_type ) );
				break;
			}
		}
	}

	bool IsConVarOnAllowList( char const *name )
	{
		CUtlSymbol sym = m_AllowList.Find( name );
		return sym.IsValid();
	}

private:
	CUtlSymbolTable m_AllowList;
} g_ConvarsVScript;

BEGIN_SCRIPTDESC_ROOT_NAMED( CScriptConvars, "CConvars", SCRIPT_SINGLETON "Provides an interface for getting and setting convars on the server." )
	DEFINE_SCRIPTFUNC( GetClientConvarValue, "Returns the convar value for the entindex as a string. Only works with client convars with the FCVAR_USERINFO flag." )
	DEFINE_SCRIPTFUNC( GetStr, "Returns the convar as a string. May return null if no such convar." )
	DEFINE_SCRIPTFUNC( GetFloat, "Returns the convar as a float. May return null if no such convar." )
	DEFINE_SCRIPTFUNC( GetInt, "Returns the convar as an integer. May return null if no such convar." )
	DEFINE_SCRIPTFUNC( GetBool, "Returns the convar as a boolean. May return null if no such convar." )
	DEFINE_SCRIPTFUNC( SetValue, "Sets the value of the convar. The convar must be in cfg/vscript_convar_allowlist.txt to be set. Supported types are bool, int, float, string." )
	DEFINE_SCRIPTFUNC( IsConVarOnAllowList, "Checks if the convar is allowed to be used and is in cfg/vscript_convar_allowlist.txt." )
END_SCRIPTDESC();
#endif

static float AttribHookValueFloat( float value, char const *szName, HSCRIPT hEntity )
{
	CBaseEntity *pEntity = ToEnt( hEntity );
	if ( !pEntity )
		return value;

	IHasAttributes *pAttribInteface = pEntity->GetHasAttributesInterfacePtr();
	if ( pAttribInteface )
	{
		string_t strAttributeClass = AllocPooledString_StaticConstantStringPointer( szName );
		float flResult = pAttribInteface->GetAttributeManager()->ApplyAttributeFloat( value, pEntity, strAttributeClass, NULL );
		value = flResult;
	}

	return value;
}

static int AttribHookValueInt( int value, char const *szName, HSCRIPT hEntity )
{
	CBaseEntity *pEntity = ToEnt( hEntity );
	if ( !pEntity )
		return value;

	IHasAttributes *pAttribInteface = pEntity->GetHasAttributesInterfacePtr();
	if ( pAttribInteface )
	{
		string_t strAttributeClass = AllocPooledString_StaticConstantStringPointer( szName );
		float flResult = pAttribInteface->GetAttributeManager()->ApplyAttributeFloat( value, pEntity, strAttributeClass, NULL );
		value = RoundFloatToInt( flResult );
	}

	return value;
}


//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CTFGameRules::RegisterScriptFunctions( void )
{
	ScriptRegisterFunctionNamed( g_pScriptVM, AttribHookValueFloat, "GetAttribFloatValue", "Fetch an attribute that is assigned to the provided weapon" );
	ScriptRegisterFunctionNamed( g_pScriptVM, AttribHookValueInt, "GetAttribIntValue", "Fetch an attribute that is assigned to the provided weapon" );
	ScriptRegisterFunction( g_pScriptVM, FX_FireBullets, "(playerIndex, origin, angles, weaponID, weaponMode, seed, spread, damage, isCritical)\nOn client: Performs all the visuals. On server: Traces damage to entities." );

#if defined( GAME_DLL )
	g_pScriptVM->RegisterInstance( &g_ConvarsVScript, "Convars" );
#endif

	if ( GetItemSchema() )
	{
		GetItemSchema()->RegisterScriptFunctions();
	}
}
