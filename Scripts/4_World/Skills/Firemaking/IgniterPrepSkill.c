class IgniterPrepSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // Ищем ближайший объект: Камин, Печь или Бочку-печь
        Object fireplace = bot.GetNearestObject("FireplaceBase", 2.0);
        if (!fireplace) return;

        // Если печь пуста и нам нужно тепло/еда
        if (NeedsHeat(bot) && !IsReadyToLight(fireplace))
        {
            PrepareSource(bot, fireplace);
        }
    }

    private void PrepareSource(ExpansionAIBase bot, Object source)
    {
        // 1. Выбираем лучший розжиг из инвентаря (Приоритет: Кора > Бумага > Тряпка > Бинт)
        ItemBase kindling = FindKindling(bot);
        if (kindling)
        {
            bot.TakeItemToHands(kindling);
            bot.StartAction(ActionAttach); // Вставить в слот розжига печи
            Print("[AN_NEKRASOV_82] Закладываю розжиг (" + kindling.GetType() + ") в " + source.GetType());
        }

        // 2. Добавляем топливо (Дрова или Палки)
        ItemBase fuel = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Firewood"));
        if (!fuel) fuel = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("WoodenStick"));
        
        if (fuel)
        {
            bot.TakeItemToHands(fuel);
            bot.StartAction(ActionAttach); // Добавить дрова
            Print("[AN_NEKRASOV_82] Добавляю дрова в топку.");
        }
    }

    private ItemBase FindKindling(ExpansionAIBase bot)
    {
        string[] types = {"Bark_Oak", "Bark_Birch", "Paper", "Rag", "BandageDressing"};
        foreach (string t : types)
        {
            ItemBase item = ItemBase.Cast(bot.GetInventory().FindEntityInInventory(t));
            if (item) return item;
        }
        return null;
    }

    private bool IsReadyToLight(Object source) { /* Проверка наличия ресурсов в слотах */ return false; }
    private bool NeedsHeat(ExpansionAIBase bot) { return bot.GetStatHeatComfort().Get() < 0; }
}

