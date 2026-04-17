/*
    РЫБОЛОВНАЯ ПАМЯТЬ: АЛЕКСЕЙ НИКОЛАЕВИЧ
    СПЕЦИАЛИЗАЦИЯ: УТИЛИЗАЦИЯ НЕГОДНЫХ СНАСТЕЙ
*/

class  NEKRASOV_Fishing_Memory
{
    // --- ⚓ ИНСПЕКЦИЯ СНАРЯЖЕНИЯ ---
    static void InspectFishingGear(PlayerBase self)
    {
        // 1. ПРОВЕРКА УДОЧКИ
        // Ищем удочку в руках или на плече
        EntityAI rod = self.GetHumanInventory().GetEntityInHands();
        if (!rod || !rod.IsInherited(FishingRod_Base))
        {
            rod = self.GetInventory().FindAttachment(InventorySlots.SHOULDER);
        }

        // Если удочка в "красном" состоянии (Ruined) — выбрасываем
        if (rod && rod.IsInherited(FishingRod_Base) && rod.IsRuined())
        {
            self.ServerDropEntity(rod);
            Print("[СВЯЗНОЙ-РЫБАЛКА] А. Николаевич: Удочка в щепки. Только лишний вес. Выбросил.");
        }

        // 2. ПРОВЕРКА КРЮЧКОВ (из предыдущего навыка)
        // Выбрасываем сломанные крючки с красным индикатором
        InspectHooks(self);
    }

    // --- 🔨 ТЕХНИЧЕСКИЙ ЦИКЛ ---
    static void MaintainTackle(PlayerBase self, EntityAI rod)
    {
        if (!rod) return;

        // Если удочка еще цела, но крючок на ней "покраснел"
        EntityAI currentHook = rod.GetAttachmentByType(InventorySlots.HOOK);
        if (currentHook && currentHook.IsRuined())
        {
            self.ServerDropEntity(currentHook);
            Print("[СВЯЗНОЙ-РЫБАЛКА] А. Николаевич: Снял и выбросил обломанный крючок.");
        }
    }
}
