graph TD
    %% Уровни подготовки
    Start{ВЫБОР МЕТОДА}
    
    Start -->|Критический голод| Picnic[УРОВЕНЬ: ПИКНИК]
    Start -->|Плановая стоянка| Chef[УРОВЕНЬ: ШЕФ-ПОВАР]

    %% Уровень Пикник
    Picnic --> Stick[Заточенная палка]
    Stick --> Roast[Жарка на огне]
    Roast --> LowCal((Низкая калорийность))

    %% Уровень Шеф-повар
    Chef --> Hygiene{ГИГИЕНА}
    Hygiene -->|Грязные руки| Wash[МЫТЬЕ РУК]
    Hygiene -->|Чистые руки| Prep[ПОДГОТОВКА]

    Prep --> Support[ОПОРА: Тренога]
    Support -->|Нет металла| TripodCraft[3 палки + веревка]
    Support -->|Есть металл| TripodIron[Металлическая тренога]

    TripodIron & TripodCraft --> Mode{РЕЖИМ}
    
    Mode -->|Вода| Boiling[ВАРКА: Кастрюля/Котелок]
    Mode -->|Жир| Baking[ЖАРКА: Сковорода]

    %% Результат
    Boiling --> Safe((Стерильность + Макс. насыщение))
    Baking --> Energy((Быстрая энергия))

    style Picnic fill:#f96,stroke:#333
    style Chef fill:#69f,stroke:#333
    style Wash fill:#ff4d4d,stroke:#000
    style Boiling fill:#00ff7f,stroke:#000
