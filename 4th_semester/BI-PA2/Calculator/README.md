Aplikace: Kalkulačka s neomezenou přesností


== Zadání


Vaším úkolem je vytvořit kalkulačku pro výpočty s neomezenou přesností. Jednotlivá čísla a výsledky operací je možné ukládat do proměnných a tyto proměnné následně využívat v dalších výpočtech.

Kalkulačka musí implementovat následující funkcionality:

Práce s celými i desetinnými čísly (především načtení a vypsání proměnných).

Základní operace: sčítání, odčítání, násobení.

Pro celá čísla implementujte navíc celočíselné dělení a zbytek po dělení.

Funkce pro zaokrouhlení, faktoriál a umocňování (exponent je celé nezáporné číslo).

Stav kalkulačky (tedy její proměnné) je možné uložit do souboru v textově čitelné formě. Stejně tak je potom možné tento stav ze souboru obnovit.

Uložení v rámci proměnných (a souboru) musí být paměťově efektivní. Při ukládání proměnné do paměti se musí určit typ daného čísla. Rozlišujte alespoň řídká čísla (obsahují především nulové hodnoty, př. 10^10) a hustá čísla (opak řídkých, př. 100! / 10^20) a podle toho určete efektivní reprezentaci.

Dále aplikace musí zpracovávat výrazy dle jednoho z následujících principů:

Základní operace (alespoň sčítání, odčítání a násobení) musí jít vnořovat pomocí závorek (př. (3 + X) * Y), závorky mohou být libovolně vnořené. Funkce a složitější operace mohou fungovat formou individuálních příkazů bez dalšího skládání (př. A = ROUND X -5).

Pro zapisování výrazů využijte prefixový (nebo postfixový) zápis, mají tu výhodu, že nevyžadují závorky a snáze se zpracovávají. V tomto případě však veškeré operace a funkce musí jít zapsat v jednom výrazu (př. A = ROUND MUL Y ADD 3 X -5).

Ukázka běhu programu: (nezávazný příklad)

IMPORT memory.calc
X = FACT 100
SCAN Y
// input from user …
Z = X / Y^20
A = ROUND Z 10
PRINT A
EXPORT memory.calc
Kde lze využít polymorfismus? (doporučené)

reprezentace čísel: řídká čísla, hustá čísla, …

operace: sčítání, odčítání, násobení, …

formáty exportu: textový, binární, …

uživatelské rozhraní: konzole, ncurses, SDL, OpenGL (různé varianty), …

Další informace:

Pro parsování výrazu se může hodit Shunting-Yard algoritmus (http://en.wikipedia.org/wiki/Shunting-yard_algorithm).

Pro uložení do souboru můžete využít i binární formát, v takovém případě dejte uživateli na výběr.

Nesnažte se ukládat čísla do textového řetězce, taková reprezentace je velice neefektivní.


== Specifikace


Pro implementace kalkulačky s neomezenou přesností bude používán algoritmus "Dijkstruv algorithm". Je založen na principu zásobníku. Pro převod jsou k dispozici dvě textové proměnné (řetězce), operatory a čísla. Každý operator má svoje prioritu. Pro realizace zásobníku a výstupní fronty je používané vektory v class CParsing.

CCalculator: Tato třída představuje hlavní aplikaci kalkulačky a pravděpodobně se stará o celkový průběh provádění. Může obsahovat metody pro příjem uživatelského vstupu, zpracování vstupního výrazu pomocí třídy Parser a vyhodnocení výrazu.

CParser: Tato třída je zodpovědná za rozbor vstupního výrazu zadaného uživatelem. Může převádět vstupní řetězec do formátu vhodného pro zpracování kalkulačkou.

CNumber: Tato třída představuje obecnou číselnou hodnotu v kalkulačce. Může sloužit jako základní třída pro CDecimalNumber a CIntegerNumber.

CDecimalNumber: Tato třída představuje desetinné číslo v kalkulačce. Dědí od třídy Number a poskytuje další vlastnosti a metody specifické pro desetinnou aritmetiku.

CIntegerNumber: Tato třída reprezentuje v kalkulačce celé číslo. Dědí od třídy Number a poskytuje další vlastnosti a metody specifické pro aritmetiku celých čísel.

COperator: Tato třída představuje v kalkulačce token operátoru. Může obsahovat vlastnosti pro uložení symbolu operátoru a definovat jeho chování při vyhodnocování výrazů.

CVariable: Tato třída může zpracovávat proměnné v kalkulačce a umožňuje uživatelům přiřazovat proměnným hodnoty a používat je ve výrazech. Může obsahovat metody pro nastavování hodnot proměnných, načítání hodnot proměnných a správu ukládání proměnných.

== Polymorfismus

Polymorfismus v tomto příkladu je využit k reprezentaci různých typů čísel a operací s nimi. Třída Number slouží jako abstraktní základ pro konkrétní typy čísel, jako jsou DecimalNumber a IntegerNumber. Díky polymorfismu můžeme pracovat s instancemi těchto tříd pomocí společného rozhraní, což nám umožňuje jednodušeji pracovat s různými typy čísel a provádět operace s nimi.

Každá třída čísla implementuje společné metody jako normalizeByExponent() pro normalizaci hodnoty čísla do standardního formátu, print() pro výpis čísla a operátory pro výpočet hodnot čísel. Tyto metody jsou definovány v abstraktní třídě Number a jsou překryty v konkrétních třídách DecimalNumber a IntegerNumber podle jejich specifických potřeb.

Další využití polymorfismu je v třídě Operator, která slouží k reprezentaci operátorů. Tato třída je abstraktní a definuje společný rozhraní pro operátory. Konkrétní operátory jako AddOperator, SubtractOperator, atd. dědí z této třídy a implementují své specifické metody. Díky tomu můžeme pracovat s různými operátory pomocí společného rozhraní a jednoduše je využívat v naší aplikaci.

Polymorfismus je také využit při implementaci třídy Visitor, která slouží k provedení akcí nad různými čísly. Konkrétní visitor, jako je DivideVisitor, implementuje metody pro provedení specifických akcí nad různými typy čísel. Díky tomu můžeme jednoduše aplikovat různé akce na čísla bez ohledu na jejich konkrétní typ.

Celkově polymorfismus v tomto příkladu umožňuje flexibilní a jednoduchou manipulaci s různými typy čísel a operacemi. Díky společnému rozhraní a využití virtuálních metod můžeme provádět operace a akce nad čísly bez ohledu na jejich skutečný typ, což zjednodušuje návrh a rozšiřování aplikace.