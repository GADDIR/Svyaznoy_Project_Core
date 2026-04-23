class MagReloaderSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || bot.IsFighting()) return;

        // 1. Условие: Есть пустой или неполный магазин + есть патроны в инвентаре
        Magazine mag = GetIncompleteMagazine(bot);
        if (mag)
        {
            FillMagazine(bot, mag);
        }
    }

    private void FillMagazine(ExpansionAIBase bot, Magazine mag)
    {
        // Ищем россыпь патронов или коробку (Box_22LR_50Rnd / Ammo_22LR)
        string ammoType = mag.GetAmmoType(); 
        ItemBase ammo = ItemBase.Cast(bot.GetInventory().FindEntityInInventory(ammoType));

        if (ammo)
        {
            bot.TakeItemToHands(mag);
            // Логика DayZ: Зарядить магазин патронами
            bot.StartAction(ActionLoadMagazine); 
            Print("[AN_NEKRASOV_82] Снаряжаю магазин патронами " + ammoType);
        }
    }

    private Magazine GetIncompleteMagazine(ExpansionAIBase bot)
    {
        // Поиск магазина в инвентаре, который не полон
        // Приоритет магазинам для MK II и IJ-70
        return null; // В реальности — перебор объектов класса Magazine
    }
}

