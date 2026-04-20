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
                // Путь должен быть: ИМЯ_ТВОЕЙ_ПАПКИ/Scripts/3_Game
                files[] = {"Svyaznoy_Project_Core/Scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"Svyaznoy_Project_Core/Scripts/4_World"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"Svyaznoy_Project_Core/Scripts/5_Mission"};
            };
        };
    };
};
