Pracujte se soubory expressions1.hpp a expressions2.hpp z minulého cvičení

1. z expressions2.hpp vytvořte expressions_variant.hpp, kde se místo dynamického polymorfismu použije std::variant
    - všechny `Value::ptr` nahraďte jen `Value`
    - `Value` už nebude polymorfní; `Int` ani `Double` nepotřebujeme
    - do `Value` schovejte detaily práce s `std::variant value_`

2. z expressions1.hpp vytvořte expressions_any.hpp podobně jako výše
    - opět, všechny detaily schovejte do `Value`
      - v expressions1.hpp bylo sčítání definováno jinde, přesuňte jej
