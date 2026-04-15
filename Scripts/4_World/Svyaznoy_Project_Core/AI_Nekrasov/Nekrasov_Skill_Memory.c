// NEKRASOV_SKILL_MEMORY.C — РЕАЛИЗАЦИЯ 13 МОДУЛЕЙ ОПЫТА
// Связь: Колледж (Блок 3), Университет (Блок 4), Армия (Блок 5)

class Nekrasov_Skill_Memory
{
    // Мапа навыков: Название -> Уровень (0.1 - 1.0)
    private ref map<string, float> m_P_SkillMatrix

    void Nekrasov_Skill_Memory()
    {
        m_P_SkillMatrix = new map<string, float>
        // Инициализация базы из Генезиса (Блоки 3-5)
        InitBaseSkills()
    }

    // РАСЧЕТ ЭФФЕКТИВНОСТИ (Влияние на геймплей)
    float GetSkillBonus(string skillName)
    {
        float level = m_P_SkillMatrix.Get(skillName)

        // Блок №5: Снайперское мастерство режет тряску рук
        if (skillName == "SVD_Ballistics")
            return 1.0 - (level * 0.8) // На максе тряска -80%

        // Блок №4: Университетская инженерия ускоряет ремонт
        if (skillName == "Radio_Engineering")
            return 1.0 + level // На максе ремонт в 2 раза быстрее

        return 1.0
    }

    // ПРОГРЕССИЯ: Учеба в процессе дела
    void PracticeSkill(string skillName, float amount)
    {
        float current = m_P_SkillMatrix.Get(skillName)
        
        if (current < 1.0)
            m_P_SkillMatrix.Set(skillName, current + amount)
            
        // Если стал Мастером — ворчим через Mumble
        if (m_P_SkillMatrix.Get(skillName) >= 1.0)
            Nekrasov_Mumble_Logic.Say("Руки-то помнят... Гатчинская школа.")
    }

    private void InitBaseSkills()
    {
        m_P_SkillMatrix.Set("SVD_Ballistics", 0.6)    // База из Армии
        m_P_SkillMatrix.Set("Radio_Engineering", 0.9) // База из Университета
        m_P_SkillMatrix.Set("Agro_Culture", 0.7)      // База Анны Петровны
        // ... и остальные до 13 модулей
    }
}
