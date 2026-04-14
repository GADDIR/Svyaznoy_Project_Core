graph TD
    %% Входной ресурс
    Input[СВЕЖИЙ ПЛОД: Грибы/Овощи/Фрукты] --> State{АНАЛИЗ СОСТОЯНИЯ}
    
    %% Логика принятия решения
    State -- "Pristine / Worn" --> Storage[Хранение / Потребление]
    State -- "Damaged / Сигнал увядания" --> Action{ВЫБОР СУШКИ}
    
    %% Методы
    Action -->|Пассивный| Pocket[КАРМАН ТТсКО: Ближе к телу]
    Action -->|Активный| Oven[ОЧАГ / БОЧКА: Принудительно]
    
    %% Результат
    Pocket & Oven --> Dried[СУШЕНЫЙ ПРОДУКТ: Dried]
    
    %% Преимущества
    Dried --> Advantage1[ВЕЧНЫЙ СРОК ГОДНОСТИ]
    Dried --> Advantage2[ВЕС: Снижение в 3-5 раз]
    Dried --> Advantage3[ВЫГОДА: Рост цены у Quinn]
    
    %% Критическая ошибка
    State -- "Игнорирование" --> Rotten((ГНИЛЬ / ВЫБРОС))
    
    style Dried fill:#d2b48c,stroke:#8b4513,color:#000
    style Rotten fill:#4b5320,stroke:#000,color:#fff
    style Action fill:#ff8c00,stroke:#333
