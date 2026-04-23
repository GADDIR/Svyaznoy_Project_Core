class AcousticAwarenessSkill
{
    private const float DANGER_NOISE_RANGE = 100.0; // Радиус фиксации чужого шума

    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Оценка собственного шума
        ManageSelfNoise(bot);

        // 2. Сканирование чужих звуков
        ListenForDanger(bot);
    }

    private void ManageSelfNoise(ExpansionAIBase bot)
    {
        // Если рядом потенциальная угроза (игрок/зомби в 50м)
        if (bot.GetTargetManager().HasPotentialTarget(50.0))
        {
            // Переходим на шаг или "гусиный шаг" (Crouch Walk)
            bot.GetNavigation().SetMovementSpeed(ExpansionHAL_MovementSpeed.WALK);
            bot.SetStance(DayZPlayerConstants.STANCE_CROUCH);
            
            // Запрет на шумные действия: рубка дров, поедание хрустящей еды
            bot.SetNoiseLock(true);
        }
    }

    private void ListenForDanger(ExpansionAIBase bot)
    {
        // Эмуляция слуха: реакция на выстрелы, шаги и голоса в радиусе DANGER_NOISE_RANGE
        if (bot.GetLastNoiseEventDist() < DANGER_NOISE_RANGE)
        {
            Print("[AN_NEKRASOV_82] Слышу подозрительный шум. Замираю.");
            bot.StartAction(ActionFreezeAndListen); // Бот замирает и пригибается
            
            // Если шум повторился - уходим в "Зеленый коридор"
            bot.GetNavigation().SetTarget(bot.GetHideoutPos(), ExpansionHAL_Mode.WALK);
        }
    }
}

