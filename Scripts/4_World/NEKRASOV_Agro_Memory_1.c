/*
    УЗЕЛ 76.1: INFRASTRUCTURE EXTENSION
    Файл: NEKRASOV_Agro_Memory_1.c (модуль инфраструктуры)
    Связь: agro_infrastructure.md
*/

modded class NEKRASOV_Agro_Memory
{
    // Реестр физических узлов на карте
    protected ref map<string, vector> m_AgroPosts; 

    override void Init()
    {
        super.Init();
        m_AgroPosts = new map<string, vector>;
        
        // Регистрация координат постов (из 14 узлов СТРУКТУРЫ)
        RegisterPost("Post_1.1.1", "4500 0 8200"); 
    }

    void RegisterPost(string name, vector pos)
    {
        m_AgroPosts.Insert(name, pos);
    }

    // Логика слежения за дистанцией до ближайшего поста
    float GetDistanceToNearestPost(vector playerPos)
    {
        float minDistance = 99999;
        foreach (string name, vector pos : m_AgroPosts)
        {
            float dist = vector.Distance(playerPos, pos);
            if (dist < minDistance) minDistance = dist;
        }
        return minDistance;
    }
}

