modded class MissionServer
{
    protected Svyaznoy_NPC m_SvyaznoyEntity; 

    override void OnInit()
    {
        super.OnInit();
        
        // --- НОВОЕ: Рапорт сервера ---
        Print("[СВЯЗНОЙ] Серверная часть миссии инициализирована. Сектор 900 под наблюдением.");

        // --- ТЕКУЩЕЕ: Материализация Некрасова ---
        vector svyaznoyPos = "319.088 284.23 246.283"; 
        vector svyaznoyOri = "180 0 0"; 

        // Спавн специализированной сущности NPC
        m_SvyaznoyEntity = Svyaznoy_NPC.Cast(GetGame().CreateObject("Svyaznoy_NPC", svyaznoyPos, false, false, true));

        if (m_SvyaznoyEntity)
        {
            m_SvyaznoyEntity.SetPosition(svyaznoyPos);
            m_SvyaznoyEntity.SetOrientation(svyaznoyOri);
            
            // Экипировка ветерана (Манифест ТТсКО)
            m_SvyaznoyEntity.GetInventory().CreateInInventory("Gorka_Pants_Summer");
            m_SvyaznoyEntity.GetInventory().CreateInInventory("Gorka_Jacket_Summer");
            m_SvyaznoyEntity.GetInventory().CreateInInventory("MilitaryBoots_Black");
            m_SvyaznoyEntity.GetInventory().CreateInInventory("PersonalRadio"); 

            m_SvyaznoyEntity.SetAllowDamage(false); 
            m_SvyaznoyEntity.GetInputController().SetDisabled(true); 
            
            Print("[СВЯЗНОЙ]: Алексей Некрасов заступил на пост. Разум и снаряжение синхронизированы.");
        }
    }
};
