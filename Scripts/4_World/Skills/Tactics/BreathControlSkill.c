class BreathControlSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. РЕЖИМ "СНАЙПЕР": Задержка дыхания при прицеливании
        if (bot.IsAiming() && bot.GetStatStamina().Get() > 20.0)
        {
            HoldBreathForPrecision(bot);
        }

        // 2. РЕЖИМ "ПРИЗРАК": Успокоение дыхания вблизи врага
        if (bot.GetTargetManager().HasPotentialTarget(15.0))
        {
            SuppressBreathingNoise(bot);
        }
    }

    private void HoldBreathForPrecision(ExpansionAIBase bot)
    {
        // Эмуляция нажатия клавиши задержки дыхания (Hold Breath)
        // Убирает качание прицела для точного выстрела из MK II
        bot.GetInputController().OverrideHoldBreath(true);
        Print("[AN_NEKRASOV_82] Задерживаю дыхание. Выстрел будет точным.");
    }

    private void SuppressBreathingNoise(ExpansionAIBase bot)
    {
        // Если бот только что бежал (стамина низкая), он будет дышать громко.
        // Навык заставляет его замереть и "продышаться" ПЕРЕД тем, как подойти к врагу.
        if (bot.GetStatStamina().Get() < 50.0)
        {
            bot.GetNavigation().Stop();
            bot.SetStance(DayZPlayerConstants.STANCE_CROUCH);
            Print("[AN_NEKRASOV_82] Успокаиваю дыхание, чтобы не выдать себя.");
        }
    }
}

