# SW-PWM pro STM32F0

Projekt obsahuje implementaci knihovny pro softwarové generování pulzně šířkové modulace `sw-pwm.c` a `sw-pwm.h`. Ke své činnosti využívá jeden časovač. Je založena na knihovně HAL od STMicroelectronics. Umožnuje generovat jak rychlé, tak i fázově korektní PWM. Dá se snadno portovat i na jiné rodiny STM32. Její využití je zamíšleno hlavně pro ovládání jesu většího množství LED.

## Použitý knihovny
Je třeba si vytvořit instanci struktury `sw_pwm_channel_t` a pojmenovat ji `sw_pwm_channel`! Tu je třeba inicializovat na GPIO která chce uživatel použít. Předpokládá se, že uživatel si GPIO nastavyl jako výstupní za použití nástroje [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html).

### Ukázka inicializace `sw_pwm_channel`
```C
// inicializace bez komparačních hodnot
volatile sw_pwm_channel_t sw_pwm_channel[] = {
    { PWM0_GPIO_Port, PWM0_Pin },
    { PWM1_GPIO_Port, PWM1_Pin },
    { PWM2_GPIO_Port, PWM2_Pin },
    { PWM3_GPIO_Port, PWM3_Pin }
};
```
Kde:
- `PWMx_GPIO_Port` je ukazatel na `GPIO_TypeDef` tedy port.
- `PWMx_Pin` číslo odpovídající konkrétnímu pinu.

```C
// inicializace s komparačními hodnotami
volatile sw_pwm_channel_t sw_pwm_channel[] = {
    { PWM0_GPIO_Port, PWM0_Pin, 0x00 },
    { PWM1_GPIO_Port, PWM1_Pin, 0x2A },
    { PWM2_GPIO_Port, PWM2_Pin, 0x7F },
    { PWM3_GPIO_Port, PWM3_Pin, 0x42 }
};
```

### Zavolání inicializační metody `sw_pwm.init(...)`
Ke kompletnímu ovládání SW PWM slouší singleton `sw_pwm`, který se nachází v souboru `sw_pwm.c` a pro korektní funkci je nutné jej inicializovat metodou `sw_pwm.init(...)`

```C
// hlavička inicializační metody
void sw_pwm.init(
    TIM_HandleTypeDef *htim_p,
    uint32_t           number_of_channels,
    uint32_t           freq,
    sw_pwm_phase_t     phase,
    sw_pwm_comp_init_t comp
);
```
Kde:
- `htop_p` ukazatel na strukturu `TIM_HandleTypeDef`, kterou vygeneruje STM32CubeMX po nastavení časovače.
- `number_of_channels` nastavuje počet kanálů.
- `freq` kmitočet generovaného PWM signálu v Hz.
- `phase` typ fázek PWM má dvě možnosti:
    * `SW_PWM_PHASE_CORRECT` fázově korektní je založena na čítání nahoru a po dosáhnutí vrcholu čítání zpět do nuly, nemůže tedy vzniknout pulz nekorektní délky při změně komparační hodnoty.
    * `SW_PWM_PHASE_INCORRECT` fázově nekorektní nekdy zvané rychlé PWM vhodné například pro ovládání LED. Je zalořenou na čítání do vrcholu a následného přetečení na nulu. výhodou této volby je dvakrát vyšší maximální frekvence než u fázově korektní volby.
- `comp` nastavení komparační úrovně má tyhle možnosti:
    * `SW_PWM_COMP_NOINIT` neovlivnujě komparační úroveň, umožnuje si nastavit komprarační hodnoty individuálně pro každý kanál externě.
    * `SW_PWM_COMP_ZERO` nastaví komparační úroveň na nulu, generuje __L__
    * `SW_PWM_COMP_HALF` komparační úroveň na polovinu rozsahu, střída __1:1__
    * `SW_PWM_COMP_FULL` komparační úroveň na plná rozsah, genuruje __H__

### Obsluha callbacku přerušení časovače
Časovači je třeba povolit přerušení při dosáhnutí vrcholu. Poté je třeba do příslušného callbacku přidat volání callbacku `sw_pwm.config_p->it_callback()`.
```C
// HAL callback dočítání časovače do stropu
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim_p)
{
    // vyhodnoce jestli toto volání způsobil náš čítač
    if (htim_p == sw_pwm.config_p->htim_p)
    {
        sw_pwm.config_p->it_callback();
    }
}
```

### Zahájení generování `sw_pwm.run()`
Po inicializaci můžeme začít generovat PWM. K zahájení generování signálu je nezbytné zavolání metody `sw_pwm.run()`. Ta vynuluje čítač a spustí časovač.

```C
// zahájení generování PWM signálu
sw_pwm.run()
```

### Nastavení komparační úrovně kanálu
K jednotlivým SW PWM kanálům je snadný přístup díky singletou `sw_pwm`.

```C
// ukázka změny prahové úrovně kanálu 2
sw_pwm.channel[2] = 127;

// ukázka změny hodnot všech kanálů
for (int i = 0; i < sw_pwm.config->number_of_channels; i++)
    sw_pwm.channel[i] = 22;
```

### Zastavení generování `sw_pwm.stop()`
Deaktivuje prerušení od časovače a nastavý všechny SW PWM kanály do logické úrovně __L__.

```C
// zastavení generování PWM signálu
sw_pwm.stop()
```

## Chování knihovny
pro vyhodnocení knihovny byl využit jeden GPIO pin jehož hodnota byla nastvena na __H__ při vstupu do callbacku obsluhy přerušení a opět nastavena do __L__ před jeho ukončením. Osciloskopem byla měřena střída jakožto informace o zatížení procesoru.

Při všech experimentech byl MCU i timer taktován na `48 MHz`.

### Vliv optimalizace na vytížení CPU
Test proběl při kmitočtu `100 Hz` a `16` aktivních kanálech.

| __OPT__ |        __POPIS__         | __VYTÍŽENÍ CPU__ |
|:-------:|:-------------------------|-----------------:|
|  `-O0`  | optimalizace off         |             57 % |
|  `-O1`  | optimalizace level 1     |             25 % |
|  `-O2`  | optimalizace level 2     |             24 % |
|  `-O3`  | optimalizace level 3     |             23 % |
|  `-Os`  | optimalizace na velikost |             33 % |

### Vliv generované frekvence na vytížení CPU
Tento test byl prováděn s `18` kanály a optimalizací `-O3`.

| __FREQ__ | __VYTÍŽENÍ CPU__ |
|--------------:|-----------------:|
|          1 Hz |              1 % |
|         10 Hz |              3 % |
|        100 Hz |             26 % |
|        200 Hz |             53 % |
|        300 Hz |             74 % |

### Vliv počtu kanálů na vytížení CPU
Tento test byl prováděn s kmitočtem `200 Hz` a optimalizací `-O3`.

| POČET KANÁLŮ | __VYTÍŽENÍ CPU__ |
|-------------:|-----------------:|
|            1 |              7 % |
|            3 |             12 % |
|            7 |             23 % |
|           10 |             31 % |
|           13 |             39 % |
|           17 |             50 % |
|           20 |             57 % |