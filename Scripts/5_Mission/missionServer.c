modded class MissionServer
{
    protected Svyaznoy_NPC m_SvyaznoyEntity; // Используем наш класс вместо PlayerBase

    override void OnInit()
    {
        super.OnInit();

        vector svyaznoyPos = "319.088 284.23 246.283"; 
        vector svyaznoyOri = "180 0 0"; 

        // СПАВН: Создаем именно Svyaznoy_NPC. "SurvivorM_Seth" — это визуальный скин (внешность).
        m_SvyaznoyEntity = Svyaznoy_NPC.Cast(GetGame().CreateObject("SurvivorM_Seth", svyaznoyPos, false, false, true));

        if (m_SvyaznoyEntity)
        {
            m_SvyaznoyEntity.SetPosition(svyaznoyPos);
            m_SvyaznoyEntity.SetOrientation(svyaznoyOri);
            
            // Экипировка ветерана (Манифест ТТсКО)
            m_SvyaznoyEntity.GetInventory().CreateInInventory("Gorka_Pants_Summer");
            m_SvyaznoyEntity.GetInventory().CreateInInventory("Gorka_Jacket_Summer");
            m_SvyaznoyEntity.GetInventory().CreateInInventory("MilitaryBoots_Black");
            m_SvyaznoyEntity.GetInventory().CreateInInventory("PersonalRadio"); 

            // Настройка состояния
            m_SvyaznoyEntity.SetAllowDamage(false); // Пока идет отладка — бессмертен
            m_SvyaznoyEntity.GetInputController().SetDisabled(true); // Запрет внешнего управления
            
            Print("[СВЯЗНОЙ]: Алексей Некрасов заступил на пост. Разум и снаряжение синхронизированы.");
        }
    }
};
