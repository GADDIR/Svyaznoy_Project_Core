class PredatorMeatBan
{
    static ref array<string> ABSOLUTE_TABOO = {
        "HumanSteakMeat",     // Человечина
        "HumanFat",           // Человеческий жир
        "WolfSteakMeat",      // Волк
        "BearSteakMeat",      // Медведь
        "ZuzSteakMeat",       // Мясо зомби (из модов)
        "ZombieMeat",         // Варианты названий мяса зомби
        "RottenMeat"          // Гнилое мясо любого вида
    };

    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        foreach (string taboo : ABSOLUTE_TABOO)
        {
            EntityAI item = bot.GetInventory().FindEntityInInventory(taboo);
            if (item)
            {
                Print("[AN_NEKRASOV_82] УГРОЗА ЗАРАЖЕНИЯ: Обнаружены останки зомби или каннибалов! Очистка инвентаря...");
                bot.PredictiveDropEntity(item);
                // После контакта с такой гадостью бот обязан помыть руки
                bot.SetBloodyHands(true); 
            }
        }
    }
}

