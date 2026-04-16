// ПРОТОКОЛ №4: РЕЕСТР ПОСТОЯННОЙ ПАМЯТИ (JSON СЕРИАЛИЗАЦИЯ)
class NEKRASOV_PersistentMemory
{
    private string m_ProfilePath = "$profile:Svyaznoy_Core/NEKRASOV_Profile.json"
    
    // СТРУКТУРА ДАННЫХ ДЛЯ JSON
    ref map<string, float>  m_Skills      // Модули навыков (0.1 - 1.0)
    ref map<string, string> m_TrustList   // ID Игрока -> Статус (Ally/Enemy)
    ref array<vector>       m_StashCoords // Координаты схронов
    bool m_OldShoulderWound               // Хроническая травма плеча

    void AN_PersistentMemory()
    {
        m_Skills = new map<string, float>
        m_TrustList = new map<string, string>
        m_StashCoords = new array<vector>
        LoadProfile()
    }

    // УЗНАВАНИЕ (Принцип дипломатии)
    string CheckIdentity(string playerID)
    {
        if (m_TrustList.Contains(playerID))
            return m_TrustList.Get(playerID)
        
        return "Neutral"
    }

    // ЗАГРУЗКА БИОГРАФИИ
    void LoadProfile()
    {
        if (FileExist(m_ProfilePath))
            JsonFileLoader<NEKRASOV_PersistentMemory>.JsonLoadFile(m_ProfilePath, this)
    }

    // СОХРАНЕНИЕ (Автосейв / Смерть / Выход)
    void SaveProfile()
    {
        JsonFileLoader<NEKRASOV_PersistentMemory>.JsonMakeFile(m_ProfilePath, this)
    }

    // ЛОГИКА НАВЫКОВ (Влияние на геймплей)
    float GetSkillMultiplier(string skillName)
    {
        if (m_Skills.Contains(skillName))
            return m_Skills.Get(skillName)
            
        return 0.1 // Базовый уровень новичка
    }

    // МЕДИЦИНСКАЯ КАРТА (Хронические дебаффы)
    void ApplyChronicEffects(PlayerBase player)
    {
        if (m_OldShoulderWound)
            player.GetInputController().SetAimNoiseMultiplier(1.5) // Руки дрожат сильнее
    }
}
