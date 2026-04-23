class ImprovisedSuppressorSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Есть оружие без глушителя + есть бутылка и скотч
        Weapon weapon = Weapon.Cast(bot.GetHumanInventory().GetEntityInHands());
        if (weapon && !HasSuppressor(weapon))
        {
            CraftAndAttach(bot, weapon);
        }
    }

    private void CraftAndAttach(ExpansionAIBase bot, Weapon weapon)
    {
        ItemBase bottle = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("WaterBottle"));
        ItemBase ductTape = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("DuctTape"));

        if (bottle && ductTape)
        {
            bot.TakeItemToHands(bottle);
            // Логика DayZ: Бутылка + Скотч = Глушитель
            bot.StartAction(ActionCreateImprovisedSuppressor);
            
            // Сразу нацепить на ствол
            bot.StartAction(ActionAttach);
            Print("[AN_NEKRASOV_82] Изготовил самодельный глушитель. Теперь можно работать тихо.");
        }
    }

    private bool HasSuppressor(Weapon weapon) {
        // Проверка слота Muzzle на наличие любого глушителя
        return weapon.FindAttachmentBySlotName("Muzzle") != null;
    }
}

