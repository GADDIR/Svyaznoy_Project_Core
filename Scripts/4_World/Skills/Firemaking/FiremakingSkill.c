class FiremakingSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Нужно согреться или приготовить еду
        if (NeedsFire(bot))
        {
            PrepareFireplace(bot);
        }
    }

    private bool NeedsFire(ExpansionAIBase bot)
    {
        // Проверяем: Холодно ли боту или есть ли в инвентаре сырое мясо/рыба
        return (bot.GetStatHeatComfort().Get() < 0 || HasRawFood(bot));
    }

    private void PrepareFireplace(ExpansionAIBase bot)
    {
        // 2. Логика создания набора для костра (из палок и коры/бумаги)
        if (!bot.GetInventory().FindEntityInInventory("Fireplace"))
        {
            bot.StartAction(ActionCreateFireplace);
            Print("[AN_NEKRASOV_82] Собираю основу для костра...");
            return;
        }

        // 3. Розжиг (используя Matchbox из его кармана)
        ItemBase matches = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Matchbox"));
        EntityAI fireplace = bot.GetInventory().FindEntityInInventory("Fireplace");

        if (matches && fireplace && !fireplace.IsIgnited())
        {
            bot.TakeItemToHands(matches);
            bot.StartAction(ActionLightItemOnFire);
            Print("[AN_NEKRASOV_82] Разжигаю огонь...");
        }
    }

    private bool HasRawFood(ExpansionAIBase bot)
    {
        return bot.GetInventory().FindEntityInInventory("Meat_Base") != null;
    }
}

