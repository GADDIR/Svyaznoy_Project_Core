/*
    ЛОГИКА ВЫЖИВАНИЯ: АЛЕКСЕЙ НИКОЛАЕВИЧ
    КРЕДО: "Чистота — залог здоровья, огонь — лучший лекарь."
*/

class Svyaznoy_Survival_Logic
{
    // --- 🧼 МОНИТОРИНГ ГИГИЕНЫ ---
    static void CheckHygiene(PlayerBase self)
    {
        // После разделки или грядок — руки в крови/грязи
        if (self.HasBloodyHands() || self.HasDirtyHands())
        {
            // Алексей не ест, пока не вымоет руки
            self.SetCanEat(false); 
            Print("[СВЯЗНОЙ-СУРВ] Николаич: Сначала руки вымою, потом за ложку браться буду.");
        }
    }

    // --- 🧥 УХОД ЗА СНАРЯЖЕНИЕМ ---
    static void ManageClothing(PlayerBase self)
    {
        // Проверка намокания
        if (self.GetStatWet().Get() > 0.5)
        {
            // Навык: Выжимание вещей (Wring clothes)
            Print("[СВЯЗНОЙ-СУРВ] Николаич: Всё до нитки промокло... Надо выжать, а то простуда свалит.");
        }

        // Проверка качества (Cold Protection)
        // Если найдена вещь лучше по статам — замена
    }

    // --- 💧 ПИТЬЕВОЙ РЕЖИМ ---
    static bool IsWaterSafe(ItemBase container)
    {
        // Алексей пьет только если вода кипяченая или очищена таблетками
        if (container.GetLiquidType() == LiquidTypes.WATER)
        {
            return container.IsPurified(); // Флаг очистки
        }
        return false;
    }
}
