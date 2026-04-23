class BagCrafting
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // Если текущий рюкзак в плохом состоянии (Ruined) или его вообще нет
        if (NeedsBetterBag(bot))
        {
            TryCraftBag(bot);
        }
    }

    private void TryCraftBag(ExpansionAIBase bot)
    {
        ItemBase rope = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Rope"));
        ItemBase sack = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("BurlapSack"));

        // ЭТАП 1: Создание сумки курьера
        if (rope && sack)
        {
            bot.TakeItemToHands(rope);
            bot.StartAction(ActionCreateCourierBag);
            Print("[AN_NEKRASOV_82] Изготавливаю сумку курьера из мешка.");
            return;
        }

        // ЭТАП 2: Модернизация до рюкзака (если есть палки)
        ItemBase courierBag = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("CourierBag"));
        ItemBase sticks = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("WoodenStick"));
        
        if (courierBag && sticks && sticks.GetQuantity() >= 3)
        {
            bot.TakeItemToHands(sticks);
            bot.StartAction(ActionCreateImprovisedBackpack);
            Print("[AN_NEKRASOV_82] Укрепляю сумку палками. Теперь это полноценный рюкзак.");
        }
    }

    private bool NeedsBetterBag(ExpansionAIBase bot)
    {
        EntityAI currentBag = bot.GetInventory().FindAttachment(InventorySlots.BACK);
        return (currentBag == null || currentBag.IsRuined());
    }
}

