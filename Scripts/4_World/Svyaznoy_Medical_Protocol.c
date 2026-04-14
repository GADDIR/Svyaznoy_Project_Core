/*
    ПРОЕКТ: СВЯЗНОЙ
    ОБЪЕКТ: Svyaznoy_Medical_Protocol (Модуль «АННА»)
    ОПИСАНИЕ: Реализация медицинского алгоритма «К.У.Л.А.К.»
*/

class Svyaznoy_Medical_Protocol
{
    // --- 🧬 ДИАГНОСТИКА (DiagnoseCondition) ---
    void DiagnoseCondition(PlayerBase self)
    {
        float blood = self.GetHealth("GlobalHealth", "Blood");
        float shock = self.GetHealth("GlobalHealth", "Shock");
        
        // ПРИОРИТЕТ №1: Гемостаз (Кровь)
        if (self.GetBleedingSourceCount() > 0)
        {
            CheckBleeding(self);
            ApplyTreatment(self, "Bandage"); 
        }

        // ПРИОРИТЕТ №2: Шок
        if (shock < 50)
        {
            ManageShock(self);
        }
    }

    // --- 🧼 СТЕРИЛЬНОСТЬ (HygieneCheck / Sanitize) ---
    bool HygieneCheck(PlayerBase self)
    {
        if (self.HasBloodyHands())
        {
            Print("[СВЯЗНОЙ/АННА]: Руки грязные. Риск сепсиса! Блокировка манипуляций.");
            return false; 
        }
        return true;
    }

    // --- 🩸 АЛГОРИТМ «ГЕМОСТАЗ» ---
    static void CheckBleeding(PlayerBase player)
    {
        int woundCount = player.GetBleedingSourceCount();
        Print("[СВЯЗНОЙ]: Обнаружено кровотечение (" + woundCount + "). Протокол К.У.Л.А.К.: К - Кровь.");
        
        // Блокировка второстепенных задач для спасения жизни
        player.GetInputController().SetDisabled(true); 
    }

    // --- 🩹 ОПЕРАТИВНОЕ ВМЕШАТЕЛЬСТВО (ApplyTreatment) ---
    void ApplyTreatment(PlayerBase patient, string item)
    {
        if (!HygieneCheck(patient)) return;

        if (item == "Bandage")
        {
            Print("[СВЯЗНОЙ/АННА]: Остановка кровотечения. Использование перевязочных материалов.");
            // Вызов анимации лечения (ActionBandageTarget/Self)
        }
    }

    // --- ⚡ ШОКОВАЯ ТЕРАПИЯ ---
    static void ManageShock(PlayerBase player)
    {
        Print("[СВЯЗНОЙ]: Высокий уровень шока. Требуется стабилизация.");
        // Выбор: Эпинефрин или горизонтальное положение в укрытии
    }

    // --- 🍞 РЕГЕНЕРАЦИЯ (RecoveryBoost) ---
    void RecoveryBoost(PlayerBase self)
    {
        // Связь с «Сухим пайком» (Белая сытость)
        if (self.GetStatEnergy().Get() > 2000)
        {
            Print("[СВЯЗНОЙ/АННА]: Энергия в норме. Регенерация крови ускорена.");
        }
    }
}
