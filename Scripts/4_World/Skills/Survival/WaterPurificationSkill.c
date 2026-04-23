class WaterPurificationSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Есть кастрюля с "сырой" водой + есть разведенный костер
        if (HasRawWaterInPot(bot) && IsFireReady(bot))
        {
            PurifyWater(bot);
        }
    }

    private void PurifyWater(ExpansionAIBase bot)
    {
        ItemBase pot = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Pot"));
        
        if (pot && !IsWaterBoiled(pot))
        {
            // Ставим кастрюлю на треногу или в костер
            bot.TakeItemToHands(pot);
            bot.StartAction(ActionAttach); 
            
            // Ждем завершения процесса кипячения (статус "Boiled")
            Print("[AN_NEKRASOV_82] Кипячу воду в кастрюле. Безопасность прежде всего.");
        }
    }

    private bool IsWaterBoiled(ItemBase pot)
    {
        // Проверка температуры и статуса воды внутри кастрюли
        return pot.GetTemperature() >= 100; 
    }

    private bool HasRawWaterInPot(ExpansionAIBase bot)
    {
        ItemBase pot = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Pot"));
        return pot && pot.GetQuantity() > 0; // В реальности добавим проверку на источник воды
    }

    private bool IsFireReady(ExpansionAIBase bot)
    {
        return bot.IsNearObject("Fireplace", 2.0);
    }
}

