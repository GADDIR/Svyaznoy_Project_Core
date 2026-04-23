class WaterSafetySkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // Ищем в инвентаре тару, которая еще не "проверена" (наша кастомная метка)
        ItemBase newBottle = GetNewUnsafeBottle(bot);
        
        if (newBottle)
        {
            // ШАГ 1: Слить всё, что там было
            if (newBottle.GetQuantity() > 0)
            {
                bot.TakeItemToHands(newBottle);
                bot.StartAction(ActionEmptyBottleBase);
                Print("[AN_NEKRASOV_82] Сливаю подозрительную воду из найденной тары.");
                return;
            }

            // ШАГ 2: Идти к колонке или кастрюле за проверенной водой
            RefillWithSafeWater(bot, newBottle);
        }
    }

    private void RefillWithSafeWater(ExpansionAIBase bot, ItemBase bottle)
    {
        // Логика: если есть кастрюля с кипятком — залить из неё.
        // Если нет — идти к ближайшей колонке.
    }
}

