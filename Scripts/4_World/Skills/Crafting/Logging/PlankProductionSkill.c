class PlankProductionSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Есть пила + есть поваленное дерево (Log)
        if (CanProducePlanks(bot))
        {
            StartSawing(bot);
        }
    }

    private bool CanProducePlanks(ExpansionAIBase bot)
    {
        // Ищем ножовку (Handsaw) или обычную пилу (Hacksaw)
        ItemBase saw = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Handsaw"));
        if (!saw) saw = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Hacksaw"));

        // Ищем бревно (Log), которое он сам срубил ранее
        EntityAI log = bot.GetInventory().FindEntityInInventory("WoodenLog");

        return (saw && log);
    }

    private void StartSawing(ExpansionAIBase bot)
    {
        ItemBase saw = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Handsaw"));
        if (!saw) saw = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Hacksaw"));

        if (saw)
        {
            bot.TakeItemToHands(saw);
            // Действие: Распилить бревно на доски
            bot.StartAction(ActionSawPlanks);
            Print("[AN_NEKRASOV_82] Распиливаю бревно на доски для обустройства базы.");
        }
    }
}

