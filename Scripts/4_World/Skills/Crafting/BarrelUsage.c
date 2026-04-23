class BarrelUsage
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        Barrel_ColorBase barrel = Barrel_ColorBase.Cast(bot.GetInventory().FindEntityInInventory("Barrel_ColorBase"));
        if (!barrel) return;

        // ЛОГИКА 1: Бочка под воду (сбор дождя)
        if (NeedsWaterStorage(bot))
        {
            PrepareWaterBarrel(bot, barrel);
        }
        // ЛОГИКА 2: Бочка под костер (безопасная печь)
        else if (NeedsFireBarrel(bot))
        {
            PrepareFireBarrel(bot, barrel);
        }
    }

    private void PrepareWaterBarrel(ExpansionAIBase bot, Barrel_ColorBase barrel)
    {
        // Для воды бочка должна быть открыта и стоять под небом
        if (!barrel.IsOpen())
        {
            bot.TakeItemToHands(barrel); // Или подойти вплотную
            bot.StartAction(ActionOpenBarrel);
            Print("[AN_NEKRASOV_82] Готовлю бочку для сбора воды.");
        }
    }

    private void PrepareFireBarrel(ExpansionAIBase bot, Barrel_ColorBase barrel)
    {
        // Чтобы сделать печь, нужны отверстия (используем нож/топор)
        ItemBase tool = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Knife_Base"));
        if (!tool) tool = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Axe_Base"));

        if (tool && !IsBarrelHoles(barrel))
        {
            bot.TakeItemToHands(tool);
            bot.StartAction(ActionCreateBarrelExhaustHoles); 
            Print("[AN_NEKRASOV_82] Прорезаю отверстия в бочке. Делаю печь.");
        }
    }

    private bool NeedsWaterStorage(ExpansionAIBase bot) { /* Проверка нужд огорода */ return true; }
    private bool NeedsFireBarrel(ExpansionAIBase bot) { /* Проверка на холод/ночь */ return true; }
    private bool IsBarrelHoles(Barrel_ColorBase barrel) { /* Проверка состояния объекта */ return false; }
}

