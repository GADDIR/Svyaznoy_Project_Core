class ShelterBuilding
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Бот находится далеко от дома или наступила ночь, а укрытия нет
        if (NeedsShelter(bot))
        {
            BuildShelter(bot);
        }
    }

    private void BuildShelter(ExpansionAIBase bot)
    {
        // Ингредиенты: Набор для укрытия (4 палки + веревка) + 50 веток (для стен)
        ItemBase shelterSite = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("ShelterSite"));
        
        // Этап 1: Создание набора (Kit), если его еще нет
        if (!shelterSite)
        {
            CraftShelterKit(bot);
            return;
        }

        // Этап 2: Сборка стен (из 50 коротких палок/веток)
        ItemBase sticks = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("WoodenStick"));
        if (sticks && sticks.GetQuantity() >= 50)
        {
            bot.StartAction(ActionBuildShelter);
            Print("[AN_NEKRASOV_82] Строю укрытие из веток для ночлега.");
        }
    }

    private void CraftShelterKit(ExpansionAIBase bot)
    {
        ItemBase rope = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Rope"));
        ItemBase longSticks = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("LongWoodenStick"));

        if (rope && longSticks && longSticks.GetQuantity() >= 4)
        {
            bot.TakeItemToHands(rope);
            bot.StartAction(ActionCreateShelterKit);
            Print("[AN_NEKRASOV_82] Изготавливаю разметку для будущего шалаша.");
        }
    }

    private bool NeedsShelter(ExpansionAIBase bot)
    {
        // Проверка: нет ли уже построенного укрытия в радиусе 20 метров
        return !bot.IsNearObject("ShelterBase", 20.0);
    }
}

