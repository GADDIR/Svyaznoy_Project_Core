class ImprovisedCrossbowSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || HasBetterWeapon(bot)) return;

        // 1. Условие: Есть доски, веревка и нож
        if (CanCraftCrossbow(bot))
        {
            CraftCrossbow(bot);
        }
    }

    private void CraftCrossbow(ExpansionAIBase bot)
    {
        ItemBase plank = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Plank"));
        ItemBase rope = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Rope"));
        ItemBase knife = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Knife_Base"));

        if (plank && rope && knife)
        {
            bot.TakeItemToHands(plank);
            // Логика DayZ: Создать ложе и механизм арбалета
            bot.StartAction(ActionCreateImprovisedCrossbow); 
            Print("[AN_NEKRASOV_82] Изготавливаю самодельный арбалет. Теперь Банов будет тихим.");
        }
    }

    private bool CanCraftCrossbow(ExpansionAIBase bot)
    {
        // Проверка всех ингредиентов для сборки
        return bot.GetInventory().FindEntityInInventory("Plank") && 
               bot.GetInventory().FindEntityInInventory("Rope") && 
               bot.GetInventory().FindEntityInInventory("WoodenStick") &&
               bot.GetInventory().FindEntityInInventory("Spear") == null; // Если есть копье, арбалет в приоритете
    }

    private bool HasBetterWeapon(ExpansionAIBase bot)
    {
        // Если уже куплен арбалет из магазина или MK II, самодельный не крафтим
        return bot.GetInventory().FindEntityInInventory("Crossbow_Black") != null;
    }
}

