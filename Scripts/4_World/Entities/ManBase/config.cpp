class CfgPatches
{
	class Svyaznoy_Project_Core
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		// Обязательно указываем мод на ИИ, который уже стоит на сервере
		requiredAddons[]={"DayZExpansion_AI_Scripts"}; 
	};
};

class CfgMods
{
	class Svyaznoy_Project_Core
	{
		type = "mod";
		dependencies[] = {"World"};
		class defs
		{
			class worldScriptModule
			{
				value = "";
				// Путь к твоим скриптам в моде
				files[] = {"Svyaznoy_Project_Core/Scripts/4_World"};
			};
		};
	};
};
