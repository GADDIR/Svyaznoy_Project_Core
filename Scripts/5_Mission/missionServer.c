modded class MissionServer
{
    protected Svyaznoy_NPC m_SvyaznoyEntity; 

    override void OnInit()
    {
        super.OnInit();

        vector svyaznoyPos = "319.088 284.23 246.283"; 
        vector svyaznoyOri = "180 0 0"; 

        // ИСПОЛЬЗУЕМ КЛАСС NPC (Он наследует внешность внутри себя или через config)
        m_SvyaznoyEntity = Svyaznoy_NPC.Cast(GetGame().CreateObject("Svyaznoy_NPC", svyaznoyPos, false, false, true));

        // Если config.cpp еще не настроен, используй "SurvivorM_Seth", 
        // но тогда в 4_World/Entities/ManBase/PlayerBase.c 
        // должна быть логика из нашего "Манифеста 1.1.0_INTEGRATED"
        
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
