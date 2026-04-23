class MedicalDiagnostics
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // Если у бота есть иконка болезни (Sick)
        if (bot.GetModifiersManager().IsModifierActive(eModifiers.MDF_SICKNESS))
        {
            DiagnoseAndTreat(bot);
        }
    }

    private void DiagnoseAndTreat(ExpansionAIBase bot)
    {
        // Если уже идет действие лекарства - ждем
        if (bot.GetModifiersManager().IsModifierActive(eModifiers.MDF_ANTIBIOTICS) || 
            bot.GetModifiersManager().IsModifierActive(eModifiers.MDF_CHARCOAL)) return;

        // 1. ПРОВЕРКА НА ПИЩЕВОЕ ОТРАВЛЕНИЕ (Salmonella/Charcoal)
        if (bot.GetModifiersManager().IsModifierActive(eModifiers.MDF_SALMONELLA))
        {
            UseMedicine(bot, "CharcoalTablets");
            Print("[AN_NEKRASOV_82] Диагноз: Отравление. Принимаю активированный уголь.");
        }
        // 2. ПРОВЕРКА НА ИНФЕКЦИЮ/ГРИПП (Influenza/Cholera)
        else if (bot.GetModifiersManager().IsModifierActive(eModifiers.MDF_INFLUENZA) || 
                 bot.GetModifiersManager().IsModifierActive(eModifiers.MDF_CHOLERA))
        {
            UseMedicine(bot, "TetracyclineAntibiotics");
            Print("[AN_NEKRASOV_82] Диагноз: Инфекция. Принимаю антибиотики.");
        }
        // 3. ПРОВЕРКА НА ПРОСТУДУ (Common Cold)
        else if (bot.GetModifiersManager().IsModifierActive(eModifiers.MDF_COLD))
        {
            UseMedicine(bot, "VitaminBottle");
            Print("[AN_NEKRASOV_82] Диагноз: Простуда. Пью витамины.");
        }
    }

    private void UseMedicine(ExpansionAIBase bot, string medicineName)
    {
        ItemBase medicine = ItemBase.Cast(bot.GetInventory().FindEntityInInventory(medicineName));
        if (medicine && medicine.GetQuantity() > 0)
        {
            bot.TakeItemToHands(medicine);
            bot.StartAction(ActionConsume);
        }
    }
}

