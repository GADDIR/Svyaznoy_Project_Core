class NEKRASOV_Brain {
    // Основной метод: "Что мне делать сейчас?"
    void DecideNextGoal(NEKRASOV_WorldState state, NEKRASOV_Memory memory) {
        if (state.GetState("is_hungry")) {
            // Ищем еду в памяти или идем искать новые здания
            return;
        }

        if (state.GetState("is_safe")) {
            // Активируем "Любопытство" - идем туда, где координаты еще не в памяти
            StartExploring();
        }
    }
}
