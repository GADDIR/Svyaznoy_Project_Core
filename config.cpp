class CfgPatches
{
	class NEKRASOV_AI_Core
	{
		units[]={};
		weapons[]={};
		requiredAddons[]={
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};

class CfgMods
{
	class NEKRASOV_AI
	{
		type = "mod";
		dependencies[] = {"Game", "World", "Mission"};
		
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"NEKRASOV_AI/Scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"NEKRASOV_AI/Scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"NEKRASOV_AI/Scripts/5_Mission"};
			};
		};
	};
};
