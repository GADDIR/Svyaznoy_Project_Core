class Svyaznoy_Medical_Protocol
{
    // Блок «Диагностика»
    void DiagnoseCondition(PlayerBase self)
    {
        float blood = self.GetHealth("GlobalHealth", "Blood");
        float shock = self.GetHealth("GlobalHealth", "Shock");
        
        if (self.IsBleeding())
        {
            ApplyTreatment(self, "Bandage"); // Приоритет №1
        }
    }

    // Блок «Стерильность»
    bool HygieneCheck(PlayerBase self)
    {
        if (self.HasBloodyHands())
        {
            Print("АННА: Руки грязные. Риск заражения!");
            return false; 
        }
        return true;
    }

    // Блок «Оперативное вмешательство» (К.У.Л.А.К.)
    void ApplyTreatment(PlayerBase patient, string item)
    {
        if (!HygieneCheck(patient)) return;

        // Логика выбора средства
        if (item == "Bandage")
        {
            Print("АННА: Остановка кровотечения.");
            // Анимация лечения
        }
    }

    // Блок «Регенерация»
    void RecoveryBoost(PlayerBase self)
    {
        // Связь с «Сухим пайком»
        if (self.GetStatEnergy().Get() > 2000)
        {
            Print("АННА: Энергия в норме. Регенерация ускорена.");
        }
    }
}
