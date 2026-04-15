// NEKRASOV_MEMORY_BUFFER.C — УПРАВЛЕНИЕ МНОГОУРОВНЕВЫМИ ДАННЫМИ
class Nekrasov_Memory_Buffer
{
    // Структуры для хранения разных типов памяти
    private ref array<ref AN_Reflex> m_E_Reflexes
    private ref map<string, vector>  m_S_Anchors
    
    // Метод "Вспомнить всё"
    void LoadFromPersistent()
    {
        // Запрос к Nekrasov_Profile.json через наш Регламент
        if (FileExist("$profile:Nekrasov_Profile.json"))
            // Загрузка навыков и списка доверия
    }

    // Очистка по регламенту (никаких ; после if)
    void PurgeOldData()
    {
        if (m_E_Reflexes.Count() > 0)
            m_E_Reflexes.Clear()
    }
}
