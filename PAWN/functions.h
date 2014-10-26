//
// Functions.h
// This file contains all the function-definitions we'll be using inside
// of the LVP Core; defined for use with our Invoke class.
// **Added all functions from invoke.pwn - CodeMatrix

#pragma once

// STRUCT: PAWN_FUNCTION
// In here we define the function's name and parameters.
struct PAWN_FUNCTION
{
	int ParamCnt;			// Number of parameters for the function
	char Function[ 33 ];		// Name of the function, ex. "GetPlayerPos"
	char Params[ 18 ];		// Parameters for the function; i f v s
};

int PawnCommand( const PAWN_FUNCTION* Command, ... );

// Definition of pawn-functions;
// --------------------------------------------
// Parameters:
//   i = integer
//   f = float value
//   s = string
//   v = variable
//   p = string var (GetPlayerName etc.)

const PAWN_FUNCTION SendClientMessage =					{ 3, "SendClientMessage",					"iis" };
const PAWN_FUNCTION SendClientMessageToAll =			{ 2, "SendClientMessageToAll",				"is" };
const PAWN_FUNCTION SendDeathMessage =					{ 3, "SendDeathMessage",					"iii" };
const PAWN_FUNCTION GameTextForAll =					{ 3, "GameTextForAll",						"sii" };
const PAWN_FUNCTION GameTextForPlayer =					{ 4, "GameTextForPlayer",					"isii" };
const PAWN_FUNCTION GetTickCount =						{ 0, "GetTickCount",						"" };
const PAWN_FUNCTION GetMaxPlayers =						{ 0, "GetMaxPlayers",						"" };
const PAWN_FUNCTION SetGameModeText =					{ 1, "SetGameModeText",						"s" };
const PAWN_FUNCTION SetTeamCount =						{ 1, "SetTeamCount",						"i" };
const PAWN_FUNCTION AddPlayerClass =					{ 11, "AddPlayerClass",						"iffffiiiiii" };
const PAWN_FUNCTION AddPlayerClassEx =					{ 12, "AddPlayerClassEx",					"iiffffiiiiii" };
const PAWN_FUNCTION AddStaticVehicle =					{ 7, "AddStaticVehicle",					"iffffii" };
const PAWN_FUNCTION AddStaticVehicleEx =				{ 8, "AddStaticVehicleEx",					"iffffiii" };
const PAWN_FUNCTION AddStaticPickup =					{ 5, "AddStaticPickup",						"iifff" };
const PAWN_FUNCTION ShowNameTags =						{ 1, "ShowNameTags",						"i" };
const PAWN_FUNCTION ShowPlayerMarkers =					{ 1, "ShowPlayerMarkers",					"i" };
const PAWN_FUNCTION GameModeExit =						{ 1, "GameModeExit",						"" };
const PAWN_FUNCTION SetWorldTime =						{ 1, "SetWorldTime",						"i" };
const PAWN_FUNCTION GetWeaponName =						{ 3, "GetWeaponName",						"ivi" };
const PAWN_FUNCTION EnableTirePopping =					{ 1, "EnableTirePopping",					"i" };
const PAWN_FUNCTION AllowInteriorWeapons =				{ 1, "AllowInteriorWeapons",				"i" };
const PAWN_FUNCTION SetWeather =						{ 1, "SetWeather",							"i" };
const PAWN_FUNCTION SetGravity =						{ 1, "SetGravity",							"f" };
const PAWN_FUNCTION AllowAdminTeleport =				{ 1, "AllowAdminTeleport",					"i" };
const PAWN_FUNCTION SetDeathDropAmount =				{ 1, "SetDeathDropAmount",					"i" };
const PAWN_FUNCTION CreateExplosion =					{ 5, "CreateExplosion",						"fffif" };
const PAWN_FUNCTION SetDisabledWeapons =				{ 0, "SetDisabledWeapons",					"" };
const PAWN_FUNCTION EnableZoneNames =					{ 1, "EnableZoneNames",						"i" };
const PAWN_FUNCTION IsPlayerAdmin =						{ 1, "IsPlayerAdmin",						"i" };
const PAWN_FUNCTION Kick =								{ 1, "Kick",								"i" };
const PAWN_FUNCTION Ban =								{ 2, "BanEx",								"is" };
const PAWN_FUNCTION BanEx =								{ 1, "Ban",									"i" };
const PAWN_FUNCTION SendRconCommand =					{ 1, "SendRconCommand",						"s" };

// a_players.inc
const PAWN_FUNCTION SetSpawnInfo =						{ 13, "SetSpawnInfo",						"iiiffffiiiiii" };
const PAWN_FUNCTION SpawnPlayer =						{ 1, "SpawnPlayer",							"i" };
const PAWN_FUNCTION SetPlayerPos =						{ 4, "SetPlayerPos",						"ifff" };
const PAWN_FUNCTION GetPlayerPos =						{ 4, "GetPlayerPos",						"ivvv" };
const PAWN_FUNCTION SetPlayerFacingAngle =				{ 2, "SetPlayerFacingAngle",				"if" };
const PAWN_FUNCTION GetPlayerFacingAngle =				{ 2, "GetPlayerFacingAngle",				"iv" };
const PAWN_FUNCTION SetPlayerInterior =					{ 2, "SetPlayerInterior",					"ii" };
const PAWN_FUNCTION GetPlayerInterior =					{ 1, "GetPlayerInterior",					"i" };
const PAWN_FUNCTION SetPlayerHealth =					{ 2, "SetPlayerHealth",						"if" };
const PAWN_FUNCTION GetPlayerHealth =					{ 2, "GetPlayerHealth",						"iv" };
const PAWN_FUNCTION SetPlayerArmour =					{ 2, "SetPlayerArmour",						"if" };
const PAWN_FUNCTION GetPlayerArmour =					{ 2, "GetPlayerArmour",						"iv" };
const PAWN_FUNCTION SetPlayerAmmo =						{ 3, "SetPlayerAmmo",						"iii" };
const PAWN_FUNCTION GetPlayerAmmo =						{ 1, "GetPlayerAmmo",						"i" };
const PAWN_FUNCTION SetPlayerTeam =						{ 2, "SetPlayerTeam",						"ii" };
const PAWN_FUNCTION GetPlayerTeam =						{ 1, "GetPlayerTeam",						"i" };
const PAWN_FUNCTION SetPlayerScore =					{ 2, "SetPlayerScore",						"ii" };
const PAWN_FUNCTION GetPlayerScore =					{ 1, "GetPlayerScore",						"i" };
const PAWN_FUNCTION SetPlayerColor =					{ 2, "SetPlayerColor",						"ii" };
const PAWN_FUNCTION GetPlayerColor =					{ 1, "GetPlayerColor",						"i" };
const PAWN_FUNCTION SetPlayerSkin =						{ 2, "SetPlayerSkin",						"ii" };
const PAWN_FUNCTION GivePlayerWeapon =					{ 3, "GivePlayerWeapon",					"iii" };
const PAWN_FUNCTION ResetPlayerWeapons =				{ 1, "ResetPlayerWeapons",					"i" };
const PAWN_FUNCTION GetPlayerWeaponData =				{ 6, "GetPlayerWeaponData",					"iiiviv " };
const PAWN_FUNCTION GivePlayerMoney =					{ 2, "GivePlayerMoney",						"ii" };
const PAWN_FUNCTION ResetPlayerMoney =					{ 1, "ResetPlayerMoney",					"i" };
const PAWN_FUNCTION SetPlayerName =						{ 2, "SetPlayerName",						"is" };
const PAWN_FUNCTION GetPlayerMoney =					{ 1, "GetPlayerMoney",						"i" };
const PAWN_FUNCTION GetPlayerState =					{ 1, "GetPlayerState",						"i" };
const PAWN_FUNCTION GetPlayerIp =						{ 3, "GetPlayerIp",							"ipi" };
const PAWN_FUNCTION GetPlayerPing =						{ 1, "GetPlayerPing",						"i" };
const PAWN_FUNCTION GetPlayerWeapon =					{ 1, "GetPlayerWeapon",						"i" };
const PAWN_FUNCTION GetPlayerKeys =						{ 7, "GetPlayerKeys",						"ivvv" };
const PAWN_FUNCTION GetPlayerName =						{ 3, "GetPlayerName",						"ipi" };
const PAWN_FUNCTION PutPlayerInVehicle =				{ 3, "PutPlayerInVehicle",					"iii" };
const PAWN_FUNCTION GetPlayerVehicleID =				{ 1, "GetPlayerVehicleID",					"i" };
const PAWN_FUNCTION RemovePlayerFromVehicle =			{ 1, "RemovePlayerFromVehicle",				"i" };
const PAWN_FUNCTION TogglePlayerControllable =			{ 2, "TogglePlayerControllable",			"ii" };
const PAWN_FUNCTION PlayerPlaySound =					{ 5, "PlayerPlaySound",						"iifff" };
const PAWN_FUNCTION SetPlayerCheckpoint =				{ 5, "SetPlayerCheckpoint",					"iffff" };
const PAWN_FUNCTION DisablePlayerCheckpoint =			{ 1, "DisablePlayerCheckpoint",				"i" };
const PAWN_FUNCTION SetPlayerRaceCheckpoint =			{ 9, "SetPlayerRaceCheckpoint",				"iifffffff" };
const PAWN_FUNCTION DisablePlayerRaceCheckpoint =		{ 1, "DisablePlayerRaceCheckpoint",			"i" };
const PAWN_FUNCTION SetPlayerWorldBounds =				{ 5, "SetPlayerWorldBounds",				"iffff" };
const PAWN_FUNCTION SetPlayerMarkerForPlayer =			{ 3, "SetPlayerMarkerForPlayer",			"iii" };
const PAWN_FUNCTION ShowPlayerNameTagForPlayer =		{ 3, "ShowPlayerNameTagForPlayer",			"iii" };
const PAWN_FUNCTION SetPlayerMapIcon =					{ 7, "SetPlayerMapIcon",					"iifffii" };
const PAWN_FUNCTION RemovePlayerMapIcon =				{ 2, "RemovePlayerMapIcon",					"ii" };
const PAWN_FUNCTION SetPlayerCameraPos =				{ 4, "SetPlayerCameraPos",					"ifff" };
const PAWN_FUNCTION SetPlayerCameraLookAt =				{ 4, "SetPlayerCameraLookAt",				"ifff" };
const PAWN_FUNCTION SetCameraBehindPlayer =				{ 1, "SetCameraBehindPlayer",				"i" };
const PAWN_FUNCTION AllowPlayerTeleport =				{ 2, "AllowPlayerTeleport",					"ii" };
const PAWN_FUNCTION IsPlayerConnected =					{ 1, "IsPlayerConnected"					"i" };
const PAWN_FUNCTION IsPlayerInVehicle =					{ 2, "IsPlayerInVehicle",					"ii" };
const PAWN_FUNCTION IsPlayerInAnyVehicle =				{ 1, "IsPlayerInAnyVehicle",				"i" };
const PAWN_FUNCTION IsPlayerInCheckpoint =				{ 1, "IsPlayerInCheckpoint",				"i" };
const PAWN_FUNCTION IsPlayerInRaceCheckpoint =			{ 1, "IsPlayerInRaceCheckpoint",			"i" };
const PAWN_FUNCTION SetPlayerTime =						{ 3, "SetPlayerTime",						"iii" };
const PAWN_FUNCTION TogglePlayerClock =					{ 2, "TogglePlayerClock",					"ii" };
const PAWN_FUNCTION SetPlayerWeather =					{ 2, "SetPlayerWeather",					"ii" };
const PAWN_FUNCTION GetPlayerTime =						{ 3, "GetPlayerTime",						"ivv" };
const PAWN_FUNCTION SetPlayerVirtualWorld =				{ 2, "SetPlayerVirtualWorld",				"ii" };
const PAWN_FUNCTION GetPlayerVirtualWorld =				{ 1, "GetPlayerVirtualWorld",				"i" };

// a_vehicle.inc
const PAWN_FUNCTION CreateVehicle =						{ 8, "CreateVehicle",						"iffffiii" };
const PAWN_FUNCTION DestroyVehicle =					{ 1, "DestroyVehicle",						"i" };
const PAWN_FUNCTION GetVehiclePos =						{ 4, "GetVehiclePos",						"ivvv" };
const PAWN_FUNCTION SetVehiclePos =						{ 4, "SetVehiclePos",						"ifff" };
const PAWN_FUNCTION GetVehicleZAngle =					{ 2, "GetVehicleZAngle",					"iv" };
const PAWN_FUNCTION SetVehicleZAngle =					{ 2, "SetVehicleZAngle",					"if" };
const PAWN_FUNCTION SetVehicleParamsForPlayer =			{ 4, "SetVehicleParamsForPlayer",			"iiii" };
const PAWN_FUNCTION SetVehicleToRespawn =				{ 1, "SetVehicleToRespawn",					"i" };
const PAWN_FUNCTION LinkVehicleToInterior =				{ 2, "LinkVehicleToInterior",				"ii" };
const PAWN_FUNCTION AddVehicleComponent =				{ 2, "AddVehicleComponent",					"ii" };
const PAWN_FUNCTION ChangeVehicleColor =				{ 3, "ChangeVehicleColor",					"iii" };
const PAWN_FUNCTION ChangeVehiclePaintjob =				{ 2, "ChangeVehiclePaintjob",				"ii" };
const PAWN_FUNCTION SetVehicleHealth =					{ 2, "SetVehicleHealth",					"if" };
const PAWN_FUNCTION GetVehicleHealth =					{ 2, "GetVehicleHealth",					"iv" };
const PAWN_FUNCTION AttachTrailerToVehicle =			{ 2, "AttachTrailerToVehicle",				"ii" };
const PAWN_FUNCTION DetachTrailerFromVehicle =			{ 1, "DetachTrailerFromVehicle",			"i" };
const PAWN_FUNCTION IsTrailerAttachedToVehicle =		{ 1, "IsTrailerAttachedToVehicle",			"i" };
const PAWN_FUNCTION SetVehicleNumberPlate =				{ 2, "SetVehicleNumberPlate",				"is" };
const PAWN_FUNCTION SetVehicleVirtualWorld =			{ 2, "SetVehicleVirtualWorld",				"ii" };
const PAWN_FUNCTION GetVehicleVirtualWorld =			{ 1, "GetVehicleVirtualWorld",				"i" };
const PAWN_FUNCTION ApplyAnimation =					{ 9, "ApplyAnimation",						"issfiiiii" };

// a_objects.inc
const PAWN_FUNCTION CreateObject =						{ 7, "CreateObject",						"iffffff" };
const PAWN_FUNCTION SetObjectPos =						{ 4, "SetObjectPos",						"ifff" };
const PAWN_FUNCTION GetObjectPos =						{ 4, "GetObjectPos",						"ivvv" };
const PAWN_FUNCTION SetObjectRot =						{ 4, "SetObjectRot",						"ifff" };
const PAWN_FUNCTION GetObjectRot =						{ 4, "GetObjectRot",						"ivvv" };
const PAWN_FUNCTION IsValidObject =						{ 1, "IsValidObject",						"i" };
const PAWN_FUNCTION DestroyObject =						{ 1, "DestroyObject",						"i" };
const PAWN_FUNCTION MoveObject =						{ 5, "MoveObject",							"iffff" };
const PAWN_FUNCTION StopObject =						{ 1, "StopObject ",							"i" };
const PAWN_FUNCTION CreatePlayerObject =				{ 8, "CreatePlayerObject",					"iiffffff" };
const PAWN_FUNCTION SetPlayerObjectPos =				{ 5, "SetPlayerObjectPos",					"iifff" };
const PAWN_FUNCTION GetPlayerObjectPos =				{ 5, "GetPlayerObjectPos",					"iivvv" };
const PAWN_FUNCTION GetPlayerObjectRot =				{ 5, "GetPlayerObjectRot",					"iivvv" };
const PAWN_FUNCTION SetPlayerObjectRot =				{ 5, "SetPlayerObjectRot",					"iifff" };
const PAWN_FUNCTION IsValidPlayerObject =				{ 2, "IsValidPlayerObject",					"ii" };
const PAWN_FUNCTION DestroyPlayerObject =				{ 2, "DestroyPlayerObject",					"ii" };
const PAWN_FUNCTION MovePlayerObject =					{ 6, "MovePlayerObject",					"iiffff" };
const PAWN_FUNCTION StopPlayerObject =					{ 2, "StopPlayerObject",					"ii" };

// Menu's
const PAWN_FUNCTION CreateMenu =						{ 6, "CreateMenu",							"siffff" };
const PAWN_FUNCTION DestroyMenu =						{ 1, "DestroyMenu",							"i" };
const PAWN_FUNCTION AddMenuItem =						{ 3, "AddMenuItem",							"iis" };
const PAWN_FUNCTION SetMenuColumnHeader =				{ 3, "SetMenuColumnHeader",					"iis" };
const PAWN_FUNCTION ShowMenuForPlayer =					{ 2, "ShowMenuForPlayer",					"ii" };
const PAWN_FUNCTION HideMenuForPlayer =					{ 2, "HideMenuForPlayer",					"ii" };
const PAWN_FUNCTION IsValidMenu =						{ 1, "IsValidMenu",							"i" };
const PAWN_FUNCTION DisableMenu =						{ 1, "DisableMenu",							"i" };
const PAWN_FUNCTION DisableMenuRow =					{ 2, "DisableMenuRow",						"ii" };

// Textdraw
const PAWN_FUNCTION TextDrawCreate =					{ 3, "TextDrawCreate",						"ffs" };
const PAWN_FUNCTION TextDrawDestroy =					{ 1, "TextDrawDestroy",						"i" };
const PAWN_FUNCTION TextDrawLetterSize =				{ 3, "TextDrawLetterSize",					"iff" };
const PAWN_FUNCTION TextDrawTextSize =					{ 3, "TextDrawTextSize",					"iff" };
const PAWN_FUNCTION TextDrawAlignment =					{ 2, "TextDrawAlignment",					"ii" };
const PAWN_FUNCTION TextDrawColor =						{ 2, "TextDrawColor",						"ii" };
const PAWN_FUNCTION TextDrawUseBox =					{ 2, "TextDrawUseBox",						"ii" };
const PAWN_FUNCTION TextDrawBoxColor =					{ 2, "TextDrawBoxColor",					"ii" };
const PAWN_FUNCTION TextDrawSetShadow =					{ 2, "TextDrawSetShadow",					"ii" };
const PAWN_FUNCTION TextDrawSetOutline =				{ 2, "TextDrawSetOutline",					"ii" };
const PAWN_FUNCTION TextDrawBackgroundColor =			{ 2, "TextDrawBackgroundColor",				"ii" };
const PAWN_FUNCTION TextDrawFont =						{ 2, "TextDrawFont",						"ii" };
const PAWN_FUNCTION TextDrawSetProportional =			{ 2, "TextDrawSetProportional",				"ii" };
const PAWN_FUNCTION TextDrawShowForPlayer =				{ 2, "TextDrawShowForPlayer",				"ii" };
const PAWN_FUNCTION TextDrawHideForPlayer =				{ 2, "TextDrawHideForPlayer",				"ii" };
const PAWN_FUNCTION TextDrawShowForAll =				{ 1, "TextDrawShowForAll",					"i" };
const PAWN_FUNCTION TextDrawHideForAll =				{ 1, "TextDrawHideForAll",					"i" };