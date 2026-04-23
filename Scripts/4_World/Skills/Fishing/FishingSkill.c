class FishingSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Время для рыбалки (например, утро или вечер, когда не работаем в поле)
        if (!IsAppropriateTime()) return;

        // 2. Проверка инструмента: Есть ли удочка в руках?
        ItemBase rod = ItemBase.Cast(bot.GetHumanInventory().GetEntityInHands());
        if (rod && rod.IsInherited(FishingRod_Base))
        {
            TryFish(bot, rod);
        }
    }

    private bool IsAppropriateTime()
    {
        int hour, minute;
        GetGame().GetWorld().GetDate(null, null, null, hour, minute);
        // Рыбачим с 6 до 9 утра или с 18 до 20 вечера
        return (hour >= 6 && hour < 9) || (hour >= 18 && hour < 20);
    }

    private void TryFish(ExpansionAIBase bot, ItemBase rod)
    {
        // 3. Проверка: Находится ли бот у воды?
        vector pos = bot.GetPosition();
        if (GetGame().GetWaterDepth(pos) <= 0) 
        {
            // Если не у воды, но есть удочка — ищем ближайший берег
            // (Логика поиска пути к ближайшей воде)
            return;
        }

        // 4. Запуск процесса рыбалки
        if (!bot.IsActionRunning())
        {
            bot.StartAction(ActionFishing);
            Print("[AN_NEKRASOV_82] Закидываю удочку...");
        }
    }
}

