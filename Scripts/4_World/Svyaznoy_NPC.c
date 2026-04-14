modded class MissionServer
{
    // 1. Меняем тип переменной на наш кастомный класс
    protected Svyaznoy_NPC m_SvyaznoyEntity; 

    override void OnInit()
    {
        super.OnInit();

        vector svyaznoyPos = "319.088 284.23 246.283"; 
        vector svyaznoyOri = "180 0 0"; 

        // 2. ГЛАВНОЕ: Создаем объект через класс Svyaznoy_NPC. 
        // Движок подтянет внешность Seth, если класс правильно прописан в config.cpp,
        // либо создаст сущность, которая немедленно инициализирует m_Brain.
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
            
            Print("[СВЯЗНОЙ]: Алексей Некрасов заступил на пост. Класс NPC инициализирован.");
        }
    }
};
