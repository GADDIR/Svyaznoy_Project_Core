class CraftingSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Нет спичек + нужен костер
        if (!HasFireStarter(bot) && NeedsFire(bot))
        {
            CraftHandDrillKit(bot);
        }
    }

    private bool HasFireStarter(ExpansionAIBase bot)
    {
        // Проверка наличия спичек или зажигалки
        return bot.GetInventory().FindEntityInInventory("Matchbox") || bot.GetInventory().FindEntityInInventory("PetrolLighter");
    }

    private void CraftHandDrillKit(ExpansionAIBase bot)
    {
        // 2. Проверка ингредиентов: Палка (Stick) + Кора (Bark)
        ItemBase stick = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("WoodenStick"));
        ItemBase bark = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Bark_Oak"));
        if (!bark) bark = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Bark_Birch"));

        if (stick && bark)
        {
            // Берем палку в руки, кору оставляем в инвентаре для крафта
            bot.TakeItemToHands(stick);
            
            // Запуск анимации крафта
            bot.StartAction(ActionCraftHandDrillKit);
            Print("[AN_NEKRASOV_82] Изготавливаю набор для розжига трением...");
        }
    }

    private bool NeedsFire(ExpansionAIBase bot)
    {
        // Холодно или есть сырая еда
        return (bot.GetStatHeatComfort().Get() < 0 || bot.GetInventory().FindEntityInInventory("Meat_Base"));
    }
}

