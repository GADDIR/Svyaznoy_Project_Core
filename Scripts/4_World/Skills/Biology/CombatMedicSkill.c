class CombatMedicSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // Бот мониторит себя и ближайших союзников в радиусе 3 метров
        LookForInjured(bot);
    }

    private void LookForInjured(ExpansionAIBase bot)
    {
        array<Man> targets = new array<Man>;
        GetGame().GetPlayers(targets);

        foreach (Man target : targets)
        {
            if (vector.Distance(bot.GetPosition(), target.GetPosition()) < 3.0)
            {
                ApplyMedicalProtocol(bot, target);
            }
        }
    }

    private void ApplyMedicalProtocol(ExpansionAIBase bot, Man target)
    {
        // 1. ОСТАНОВКА КРОВИ (Самое важное)
        if (target.IsBleeding())
        {
            PerformAction(bot, target, "BandageDressing", ActionBandageTarget);
            return;
        }

        // 2. ПОДЪЕМ ИЗ ОБМОРОКА
        if (target.IsUnconscious())
        {
            if (HasItem(bot, "Epinephrine")) 
                PerformAction(bot, target, "Epinephrine", ActionInjectTarget);
            else 
                bot.StartAction(ActionWakeUpTarget);
            return;
        }

        // 3. БОЛЬ И ПЕРЕЛОМЫ
        if (target.GetModifiersManager().IsModifierActive(eModifiers.MDF_BROKEN_LEGS))
        {
            PerformAction(bot, target, "Splint", ActionApplySplintTarget);
            return;
        }
    }
}

