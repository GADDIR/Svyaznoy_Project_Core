modded class PlayerBase
{
    // [ШВ: ИНЪЕКЦИЯ ПЕРЕМЕННЫХ]
    protected float m_Svyaz_Stress = 0.0;
    protected float m_Svyaz_ScanTimer = 0.0;
    protected vector m_Svyaz_LastSoundPos = "0 0 0";

    // 1. Инициализация (Этап I) - остается без изменений
    override void StartingEquipSetup(bool is_new_player)
    {
        super.StartingEquipSetup(is_new_player);
        string player_uid = GetIdentity().GetId();
        if (player_uid == "76561198067049765") 
        {
            RemoveAllItems();
            GetInventory().CreateInInventory("TTsKOJacket_Camo");
            GetInventory().CreateInInventory("TTsKOPants_Camo");
            GetInventory().CreateInInventory("CombatBoots_Black");
            GetInventory().CreateInInventory("HighCapacityVest_Black");

            EntityAI radio = GetInventory().CreateInInventory("PersonalRadio");
            if (radio) radio.GetInventory().CreateAttachment("Battery9V");
            
            // ... остальной лут (нож, еда) согласно V1
            Print("[Связной]: Некрасов А.Н. материализован.");
        }
    }

    // 2. Активация "Мозга" (Этап III)
    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        
        // Запуск процессора сенсоров только для Маверика
        if (GetIdentity() && GetIdentity().GetId() == "76561198067049765")
        {
            Svyaznoy_SensoryProcessor(timeslice);
        }
    }

    // [ШВ: ВНЕДРЕНИЕ ЛОГИКИ ША]
    void Svyaznoy_SensoryProcessor(float timeslice)
    {
        if (m_Svyaz_Stress > 0) m_Svyaz_Stress -= 0.01 * timeslice; 

        if (GetVelocity().Length() < 0.1)
        {
            m_Svyaz_ScanTimer += timeslice;
            if (m_Svyaz_ScanTimer >= 1.5) 
            {
                ExecuteSvyaznoyScan();
                m_Svyaz_ScanTimer = 0;
            }
        }
        else { m_Svyaz_ScanTimer = 0; }
    }

    void ExecuteSvyaznoyScan()
    {
        float dynamicFOV = 110.0 - (m_Svyaz_Stress * 40.0);
        Print("[Связной_ПСЛ]: Сканирование... Сектор: " + dynamicFOV + " | Стресс: " + m_Svyaz_Stress);
        
        // Здесь будет Raycast-фильтр целей
    }
}
