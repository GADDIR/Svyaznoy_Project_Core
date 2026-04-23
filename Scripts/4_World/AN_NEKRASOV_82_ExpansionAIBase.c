modded class ExpansionAIBase
{
    // Ссылки на модули навыков Некрасова
    ref FarmerSkill m_Nekrasov_Farmer;
    ref SurvivalSkill m_Nekrasov_Survival;

    override void EEInit()
    {
        super.EEInit();

        // Инициализация сознания ТОЛЬКО для этого ID
        if (GetIdentityName() == "AN_NEKRASOV_82")
        {
            m_Nekrasov_Farmer = new FarmerSkill();
            m_Nekrasov_Survival = new SurvivalSkill();
            
            Print("[AN_NEKRASOV_82] Сознание инициализировано успешно.");
        }
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        
        // Запуск циклов мышления, если модули созданы
        if (m_Nekrasov_Survival)
            m_Nekrasov_Survival.OnUpdate(this);

        if (m_Nekrasov_Farmer)
            m_Nekrasov_Farmer.OnUpdate(this);
    }
}

