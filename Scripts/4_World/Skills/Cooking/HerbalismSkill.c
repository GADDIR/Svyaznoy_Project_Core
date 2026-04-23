class HerbalismSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Есть кастрюля с водой на огне + найдены ягоды/травы
        if (CanBrewTea(bot))
        {
            StartBrewing(bot);
        }
    }

    private bool CanBrewTea(ExpansionAIBase bot)
    {
        // Проверяем наличие ингредиентов: Шиповник (Canina) или Бузина (Sambucus)
        ItemBase herbs = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("CaninaBerry"));
        if (!herbs) herbs = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("SambucusBerry"));

        // Проверяем кастрюлю с водой (Pot)
        ItemBase pot = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Pot"));
        
        return (herbs && pot && IsFireActive(bot));
    }

    private void StartBrewing(ExpansionAIBase bot)
    {
        ItemBase herbs = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("CaninaBerry"));
        if (!herbs) herbs = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("SambucusBerry"));
        
        EntityAI pot = bot.GetInventory().FindEntityInInventory("Pot");

        if (herbs && pot)
        {
            // Добавляем ягоды в кастрюлю
            bot.TakeItemToHands(herbs);
            bot.StartAction(ActionAttach); 
            Print("[AN_NEKRASOV_82] Завариваю целебный отвар из ягод.");
        }
    }

    private bool IsFireActive(ExpansionAIBase bot)
    {
        return bot.IsNearObject("Fireplace", 2.0); // Бот понимает, что нужен жар костра
    }
}

