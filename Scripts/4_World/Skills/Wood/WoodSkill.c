class WoodSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Нужны дрова (если холодно или близится ночь)
        if (NeedsFirewood(bot))
        {
            GatherFuel(bot);
        }
    }

    private bool NeedsFirewood(ExpansionAIBase bot)
    {
        // Проверяем: температура падает или скоро вечер
        int hour, minute;
        GetGame().GetWorld().GetDate(null, null, null, hour, minute);
        return (hour >= 19 || bot.GetStatHeatComfort().Get() < 0);
    }

    private void GatherFuel(ExpansionAIBase bot)
    {
        // Ищем ближайший куст или дерево
        Object target = GetNearestWoodSource(bot, 10.0);
        if (!target) return;

        ItemBase tool = ItemBase.Cast(bot.GetHumanInventory().GetEntityInHands());
        
        // 2. Если есть топор - рубим дерево
        if (tool && (tool.IsInherited(Axe_Base) || tool.IsInherited(Hatchet)))
        {
            bot.StartAction(ActionChopTree);
        }
        // 3. Если топора нет - ломаем куст руками (получаем палки)
        else
        {
            bot.StartAction(ActionCollectShortSticks);
        }
        
        Print("[AN_NEKRASOV_82] Собираю топливо для костра...");
    }

    private Object GetNearestWoodSource(ExpansionAIBase bot, float range)
    {
        // Логика поиска деревьев и кустов в радиусе
        // Используем стандартные фильтры DayZ для растительности
        return null; // В реальном коде тут будет поиск по типам "Tree" и "Bush"
    }
}

