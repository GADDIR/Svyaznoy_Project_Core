class StoneKnifeSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || HasGoodKnife(bot)) return;

        // 1. Ищем камни в инвентаре
        ItemBase stone1 = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("SmallStone"));
        
        if (stone1)
        {
            // 2. Ищем второй камень (в стеке или отдельный)
            ItemBase stone2 = GetSecondStone(bot, stone1);
            
            if (stone2)
            {
                // ЕДИНСТВЕННЫЙ способ для камня: совмещение в руках
                StartStoneCraft(bot, stone1, stone2);
            }
            else
            {
                // Если камень один — даем команду "Навыку добычи" искать второй
                // Алексей Николаевич понимает: "Об скалу камень не наточить"
                bot.StartAction(ActionSearchRocks); 
            }
        }
    }

    private void StartStoneCraft(ExpansionAIBase bot, ItemBase s1, ItemBase s2)
    {
        bot.TakeItemToHands(s1);
        // Логика DayZ: объединить s1 и s2 для получения StoneKnife
        bot.StartAction(ActionCreateStoneKnife); 
        Print("[AN_NEKRASOV_82] Изготавливаю каменный нож (совмещение двух камней).");
    }

    private ItemBase GetSecondStone(ExpansionAIBase bot, ItemBase firstStone)
    {
        // Проверяем, нет ли в руках/инвентаре еще одного камня
        return ItemBase.Cast(bot.GetInventory().FindEntityInInventory("SmallStone")); 
        // В реальном коде добавим проверку, чтобы не выбрать тот же самый объект
    }

    private bool HasGoodKnife(ExpansionAIBase bot)
    {
        return bot.GetInventory().FindEntityInInventory("Knife_Base") != null;
    }
}

