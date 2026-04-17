class CfgPatches
{
	class Svyaznoy_Project_Core
	{
		units[] = {};
		weapons[] = {};
		requiredAddons[] = {"DZ_Data", "DZ_Scripts"}; // Базовая зависимость
	};
};

class CfgMods
{
	class Svyaznoy_Project_Core
	{
		type = "mod";
		dependencies[] = {"World"}; // Указываем, что работаем в 4_World
		
		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = {"Svyaznoy_Project_Core/Scripts/4_World/NEKRASOV_FINAL_INIT.c"}; 
				// ^^^ Тот самый путь к нашему Монолиту
			};
		};
	};
};

