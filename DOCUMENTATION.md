PA2 Semestrální práce, Kryštof Klen
Téma - Šachy

Požadavky:
	Minimální velikost terminálu: minimálně 50 sloupců a 43 řádek
	Ovládání: Pomocí šipek, s = select , m = move, q = quit and save, CTRL + C = quit without saving


----------------------------------------------------------------------------------
Architektura hry:
Ve hře používám NCURSES, díky čemuž vytvořím v terminálu GUI, terminál musí mít povolené barvy,
jinak od sebe nepudou některé věci rozlišit.

Hra je rozdělena do 5 složek: API, APPLICATION, FileOperations, Gaame, UI

HLAVNÍ FILOSOFIÍ JE ODDĚLIT OD SEBE UI A KONTROLU HRY (aby se pak mohlo např. napasovat na SDL nebo jinou grafickou knihovnu)

----------------------------------------------------------------------
UI:
	Obsahuje vše, co nějakým způsobem používá NCURSES.
	Účelem kódu v tomto adresáři je jen cistě zobrazení
	a UI. Když např. hráč chce provést nepatný tah, tak 
	kód v UI mu v tom nezabrání. O to se starají třídy
	v adresáři LOGIC.
	Jediné, co se v UI kontroluje, jsou věci, které jsou 
	s UI přímo spjaté (např. aby člověk když vzbírá pozici 
	nevyjel z obrazovky atd..)
	Některé věci v UI by asi šly navrhnout možná o chlup
	efektivněji, nicméně náročné operace (zejména generování různých tahů v MINMAX bude probíhat v LOGIC a UI se nedotkne)

--------------------------------------------------------------------
Game:
	Rozdělená na další 3 podadresáře

-----------------------------------------------------------------
AI: 
	Zde jsou algorytmy ovládající šachy ve hře proti počítači,
	jsou 3 úrovně : easy - náhodné tahy, mid - vebere se tah, se kterým vehodím
	figurku s největší vahou, difficult - použití alg. minmax - vždy se kouknu
	3 tahy dopředu a veberu nejlepší možnost, v případě, že min max nalezne vícero stejně ohodnocených tahů, vybere náhodný z nich.

------------------------------------------------------------------------	

Core: 
	Implementace základních entit pro hru...Figurka, Pozice, kontrola tahů atd..
	Tyto entity jsou vidět v obrázcích, že jsou to opravdu základní kameny, na kterých pak herní logika staví.

------------------------------------------------------------------------
GameControl: 
	Herní smyčka..
	Z této třídy dělí OnePlayerGame a TwoPlayersGame, s využitím polymorfismu lze poté 
	hru jedodušeji ovládat z vyšších vrstev.

------------------------------------------------------------------------
FileOperations:
	Má na starosti čtení a načítání ze souboru.

------------------------------------------------------------------------
Application: 
	Zajištuje start aplikace a první kontakt s entry pointem (main.cpp)
	
------------------------------------------------------------------------
API:
	Zajištuje komunikaci mezi herní logikou, UI a FileOpearations,
	dalo by se říci, že slepujedohromady jednotlivé kusy programu, které jsem
	se snažil implementovat tak, aby na sobě byli nezávislé.





