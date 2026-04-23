class TorchCrafting
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || HasLightSource(bot)) return;

        // Ищем тряпки (Rag) — они нужны для обоих видов факелов
        ItemBase rags = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Rag"));
        if (!rags) return;

        // ВАРИАНТ 1: Длинная палка (LongWoodenStick) — большой факел
        ItemBase longStick = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("LongWoodenStick"));
        if (longStick)
        {
            CraftTorch(bot, longStick, rags);
            return;
        }

        // ВАРИАНТ 2: Короткая палка (WoodenStick) — маленький факел
        ItemBase shortStick = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("WoodenStick"));
        if (shortStick)
        {
            CraftTorch(bot, shortStick, rags);
        }
    }

    private void CraftTorch(ExpansionAIBase bot, ItemBase stick, ItemBase rags)
    {
        bot.TakeItemToHands(stick);
        // Логика DayZ: Соединить палку и тряпку
        bot.StartAction(ActionCreateTorch);
        Print("[AN_NEKRASOV_82] Изготавливаю факел для освещения пути.");
    }

    private bool HasLightSource(ExpansionAIBase bot)
    {
        // Если уже есть горящий факел или рабочий фонарик, новый не крафтим
        return bot.GetInventory().FindEntityInInventory("Torch") != null;
    }
}

