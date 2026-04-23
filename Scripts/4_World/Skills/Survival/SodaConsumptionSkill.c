class SodaConsumptionSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || bot.IsFighting()) return;

        // 1. Условие: Жажда ниже нормы или нужна энергия для бега
        if (NeedsDrink(bot) || bot.GetStatStamina().Get() < 10.0)
        {
            ConsumeSoda(bot);
        }
    }

    private void ConsumeSoda(ExpansionAIBase bot)
    {
        // Поиск любой банки: Cola, Kvass, Pipsi, Mad-Monk
        ItemBase soda = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("SodaCan_ColorBase"));
        
        if (soda)
        {
            bot.TakeItemToHands(soda);
            bot.StartAction(ActionConsume); 
            Print("[AN_NEKRASOV_82] Открываю газировку. Нужно восстановить силы.");
            
            // После употребления сработает логика утилизации мусора
        }
    }

    private bool NeedsDrink(ExpansionAIBase bot) {
        return bot.GetStatWater().Get() < 2000.0;
    }
}

