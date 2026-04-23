class WellHydrationSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || bot.IsFighting()) return;

        // Ищем колонку (Well)
        Object well = bot.GetNearestObject("StaticObj_RoadCone", 2.0);
        if (well && NeedsDrink(bot))
        {
            ProcessDrinking(bot, well);
        }
    }

    private void ProcessDrinking(ExpansionAIBase bot, Object well)
    {
        // ШАГ 1: ГИГИЕНА. Если руки в крови - сначала моем!
        if (bot.HasBloodyHands())
        {
            bot.StartAction(ActionWashHandsWell);
            Print("[AN_NEKRASOV_82] Руки в крови! Сначала мою, потом пью.");
            return; 
        }

        // ШАГ 2: ПИТЬЕ. Пьем руками до упора
        if (!bot.GetModifiersManager().IsModifierActive(eModifiers.MDF_STOMACH)) // Пока нет иконки желудка
        {
            bot.StartAction(ActionDrinkWellContinuous); 
            Print("[AN_NEKRASOV_82] Пью из колонки досыта. Запас воды на максимум.");
        }
    }

    private bool NeedsDrink(ExpansionAIBase bot)
    {
        // Пьем, если вода ниже 90%, чтобы всегда быть в тонусе
        return bot.GetStatWater().Get() < 4500.0; 
    }
}

