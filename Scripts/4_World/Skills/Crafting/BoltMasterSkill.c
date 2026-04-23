class BoltMasterSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. СБОР: Если бой окончен, ищем выпущенные болты
        if (!bot.IsFighting())
        {
            CollectUsedBolts(bot);
        }

        // 2. КРАФТ: Если болтов мало, делаем новые из того, что есть в карманах
        if (NeedsAmmo(bot))
        {
            CraftBestAvailableBolt(bot);
        }
    }

    private void CraftBestAvailableBolt(ExpansionAIBase bot)
    {
        ItemBase stick = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("WoodenStick"));
        ItemBase feather = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("ChickenFeather"));
        if (!stick || !feather) return;

        ItemBase knife = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Knife_Base"));
        ItemBase bone = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Bone"));
        ItemBase stone = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("SmallStone"));

        bot.TakeItemToHands(knife);

        if (bone) {
            // Приоритет №1: Костяной болт
            bot.StartAction(ActionCreateBoneBolt);
            Print("[AN_NEKRASOV_82] Изготавливаю тяжелый костяной болт.");
        } else if (stone) {
            // Приоритет №2: Каменный болт
            bot.StartAction(ActionCreateStoneBolt);
            Print("[AN_NEKRASOV_82] Вытачиваю болт с каменным наконечником.");
        } else {
            // Приоритет №3: Простой болт
            bot.StartAction(ActionCreateSimpleBolt);
            Print("[AN_NEKRASOV_82] Делаю легкий болт с оперением.");
        }
    }

    private void CollectUsedBolts(ExpansionAIBase bot)
    {
        // Поиск объектов болтов в радиусе 5 метров от бота после стрельбы
        EntityAI bolt = EntityAI.Cast(bot.GetNearestObject("Ammo_Expansion_CrossbowBolt", 5.0));
        if (bolt && bot.GetInventory().CanAddEntityIntoInventory(bolt))
        {
            bot.TakeEntityToInventory(InventoryMode.PREDICTIVE, bolt);
            Print("[AN_NEKRASOV_82] Подобрал уцелевший болт. Экономия.");
        }
    }

    private bool NeedsAmmo(ExpansionAIBase bot) {
        return bot.GetInventory().CountItemsWithPrefix("Ammo_Expansion_CrossbowBolt") < 10;
    }
}

