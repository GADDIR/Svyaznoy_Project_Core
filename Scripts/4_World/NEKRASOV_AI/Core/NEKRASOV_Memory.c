class NEKRASOV_Memory {
    // Внутренняя карта Маверика: Координаты -> Описание места
    protected ref map<vector, string> m_KnownLocations = new map<vector, string>;

    // Метод: Запомнить увиденное
    void Memorize(vector pos, string type) {
        if (!IsAlreadyKnown(pos)) {
            m_KnownLocations.Insert(pos, type);
            Print("NEKRASOV AI: Я запомнил новое место: " + type + " на " + pos.ToString());
        }
    }

    // Проверка: Был ли я тут раньше?
    bool IsAlreadyKnown(vector pos) {
        // Логика сравнения координат с небольшим допуском
        return false; 
    }

    // Поиск ближайшего известного ресурса (например, еды)
    vector GetClosestKnown(vector currentPos, string type) {
        // Маверик перебирает свою память, а не базу данных сервера
        return "0 0 0";
    }
}
