class BasicSanitationSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. ПРИОРЯТЕТ: Мытье рук после крови (предотвращение сальмонеллы)
        if (bot.HasBloodyHands())
        {
            WashHandsLogic(bot);
        }

        // 2. ОБРАБОТКА ПОРИЗОВ: Дезинфекция перед перевязкой
        if (bot.IsBleeding())
        {
            DisinfectWounds(bot);
        }
    }

    private void WashHandsLogic(ExpansionAIBase bot)
    {
        // Ищем воду (бутылка/колонка) или дезинфектант
        ItemBase cleaner = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("AlcoholPreps"));
        if (!cleaner) cleaner = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("WaterBottle"));

        if (cleaner)
        {
            bot.TakeItemToHands(cleaner);
            bot.StartAction(ActionWashHandsWell); 
            Print("[AN_NEKRASOV_82] Мою руки. Зараза не пройдет.");
        }
    }

    private void DisinfectWounds(ExpansionAIBase bot)
    {
        ItemBase iodine = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("IodineTincture"));
        if (!iodine) iodine = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("AlcoholPreps"));

        if (iodine)
        {
            bot.TakeItemToHands(iodine);
            bot.StartAction(ActionDisinfectSelf);
            Print("[AN_NEKRASOV_82] Обрабатываю порез антисептиком.");
        }
    }
}

