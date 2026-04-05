cpp
modded class MissionServer
{
    protected PlayerBase m_SvyaznoyEntity;
    override void OnInit()
    {
        super.OnInit();
        vector svyaznoyPos = "319.088 284.23 246.283"; 
        vector svyaznoyOri = "180 0 0"; 
        m_SvyaznoyEntity = PlayerBase.Cast(GetGame().CreateObject("SurvivorM_Seth", svyaznoyPos, false, false, true));
        if (m_SvyaznoyEntity)
        {
            m_SvyaznoyEntity.SetPosition(svyaznoyPos);
            m_SvyaznoyEntity.SetOrientation(svyaznoyOri);
            m_SvyaznoyEntity.SetAllowDamage(false); 
            m_SvyaznoyEntity.GetInventory().CreateInInventory("Gorka_Pants_Summer");
            m_SvyaznoyEntity.GetInventory().CreateInInventory("Gorka_Jacket_Summer");
            m_SvyaznoyEntity.GetInventory().CreateInInventory("MilitaryBoots_Black");
            m_SvyaznoyEntity.GetInventory().CreateInInventory("PersonalRadio"); 
            m_SvyaznoyEntity.GetInputController().SetDisabled(true); 
            Print("[Связной]: Алексей Некрасов заступил на пост 319/284/246. Эфир чист.");
        }
    }
};
