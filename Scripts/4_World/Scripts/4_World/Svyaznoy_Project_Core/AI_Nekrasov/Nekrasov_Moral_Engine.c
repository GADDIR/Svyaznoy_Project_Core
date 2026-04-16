class Nekrasov_Moral_Engine {
    // Наследие (Legacy)
    float m_AnnaStrictness = 0.9;   // Порядок
    float m_NikolayIntegrity = 1.0; // Честность
    float m_IgishevDiscipline = 0.8; // Сила

    bool CheckMoralAction(string actionName) {
        if (actionName == "Steal") return false;
        if (actionName == "EatPig") return false;
        return true;
    }
}
