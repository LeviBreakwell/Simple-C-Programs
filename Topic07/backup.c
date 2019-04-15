#include <avr/io.h>
#include <util/delay.h>
#include <cpu_speed.h>
#include <macros.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <lcd_model.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <graphics.h>
#include <lcd.h>
#include <sprite.c>
#include <cpu_speed.h>
int lives = 10;
int score = 0;
bool alreadyhit = false;
float herospeed = 0.5;
bool gamepaused = false;
bool gameStart = false;
bool oddsafe[28];
bool evensafe[28];
bool dead = false;
bool moving = false;
float platformspeed = 0.2;
bool treasurePause = false;
Sprite hero;
Sprite startplatform;
Sprite oddplatforms[28];
Sprite evenplatforms[28];
Sprite treasure;

volatile uint32_t overflow_count = 0;


#define FREQ (8000000.0)
#define PRESCALE (1024.0)
double get_elapsed_time()
{
    return (overflow_count * 65536.0 + TCNT1) * PRESCALE / FREQ;
}

// BITMAPS FOR HERO, PLATFORMS AND TREASURE
uint8_t platformSafeImg[4] = {
    0b11111111,
    0b11000000,
    0b11111111,
    0b11000000,
};
uint8_t platformDangerImg[4] = {
    0b10101010,
    0b10000000,
    0b11111111,
    0b11000000,
};

static uint8_t treasureImg[4] = {
    0b10100000,
    0b11100000,
};
static uint8_t heroImg[3] = {
    0b11100000,
    0b01000000,
    0b10100000,
};

//setting up joyset and controls
void setup_joystick(void)
{
    CLEAR_BIT(DDRD, 1);
    CLEAR_BIT(DDRB, 7);
    CLEAR_BIT(DDRB, 1);
    CLEAR_BIT(DDRD, 0);
    CLEAR_BIT(DDRB, 0);
    CLEAR_BIT(DDRF, 5);
    CLEAR_BIT(DDRF, 6);
}

void draw_int(uint8_t x, uint8_t y, int t)
{
    char snum[100];
    snprintf(snum, 10, "%d", t);
    draw_string(x, y, snum, FG_COLOUR);
}

void draw_formatted(int x, int y, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    char buffer[500];
    vsprintf(buffer, format, args);
    draw_string(x, y, buffer, FG_COLOUR);
}

int oddcounter = 0;
int evencounter = 0;

//FUNCTION THAT CREATES ALL PLATFORMS
void create_platforms()
{
    //variables used to distinguish between safe and dangerous platforms, and whether the platform is there or not
    oddcounter = 0;
    evencounter = 0;

    int safeornot = 0;
    int thereornot = 0;

    sprite_init(&startplatform, 37, 5, 10, 2, platformSafeImg);
    srand(TCNT1);
    for (int row = 1; row <= 3; row++)
    {
        for (int column = 1; column <= 6; column++)
        {
            //randomising the safe and dangerous a ratio of 1:3 and ther or not at 1:3
            safeornot = rand() % 3;
            thereornot = rand() % 3;
            //determines whether the row is odd or even
            if (row % 2 == 1)
            {
                //checks if platform is there, if not just passes
                if (thereornot != 1)
                {
                    //checks to make safe or dangerous platform
                    if (safeornot != 1)
                    {
                        sprite_init(&oddplatforms[oddcounter], (column - 1) * 13, (row * 10) + 5, 10, 2, platformSafeImg);

                        oddsafe[oddcounter] = true;
                        oddcounter++;
                        oddplatforms[oddcounter].dx = platformspeed;
                    }
                    else
                    {
                        sprite_init(&oddplatforms[oddcounter], (column - 1) * 13, (row * 10) + 5, 10, 2, platformDangerImg);
                        oddsafe[oddcounter] = false;
                        oddcounter++;
                        oddplatforms[oddcounter].dx = platformspeed;
                    }
                }
                //oddplatforms[oddcounter].dx = platformspeed;
            }
            //creating even rows
            else
            {
                if (thereornot != 1)
                {
                    if (safeornot != 1)
                    {
                        sprite_init(&evenplatforms[evencounter], (column - 1) * 13, (row * 10) + 5, 10, 2, platformSafeImg);
                        evensafe[evencounter] = true;
                        evencounter++;
                        evenplatforms[evencounter].dx = platformspeed;
                    }
                    else
                    {
                        sprite_init(&evenplatforms[evencounter], (column - 1) * 13, (row * 10) + 5, 10, 2, platformDangerImg);
                        evensafe[evencounter] = false;
                        evencounter++;
                        evenplatforms[evencounter].dx = platformspeed;
                    }
                }
                //evenplatforms[evencounter].dx = -platformspeed;
            }
        }
    }
}



//function that controls movement of treasure
void treasuremovement()
{
    if (BIT_IS_SET(PINF, 5))
    {
        treasurePause = !treasurePause;
    }
    if (!treasurePause)
    {
        treasure.x += treasure.dx;
        if (treasure.x <= 1 || treasure.x >= LCD_X - treasure.width - 1)
        {
            treasure.dx = -treasure.dx;
        }
    }
}

bool sprites_collision(Sprite sprite1, Sprite sprite2)
{
    //declaring variables for collision
    int sprite1bot = round(sprite1.y) + sprite1.height;
    int sprite1top = round(sprite1.y) + 1;
    int sprite1left = round(sprite1.x) + 1;
    int sprite1right = round(sprite1.x) + sprite1.width - 1;
    int sprite2right = round(sprite2.x) + sprite2.width;
    int sprite2left = round(sprite2.x);
    int sprite2top = round(sprite2.y);
    int sprite2bot = round(sprite2.y) + sprite1.height;
    //testing if player has collided with a safe platform
    if (sprite1bot < sprite2top)
    {
        return false;
    }
    if (sprite1left > sprite2right)
    {
        return false;
    }
    if (sprite1right < sprite2left)
    {
        return false;
    }
    if (sprite1top > sprite2bot)
    {
        return false;
    }
    else
    {
        return true;
    }
}

sprite_id sprite_collision_any(Sprite p, Sprite platformss[], int num)
{
    sprite_id result = NULL;
    for (int i = 0; i < num; i++)
    {
        if (sprites_collision(p, platformss[i]))
        {
            result = &platformss[i];
            break;
        }
    }
    return result;
}
int direction = 0;
void playermovement()
{
    if (hero.y == LCD_Y - 2)
    {
        lives--;
        hero.x = 40;
        hero.y = 1;
        hero.dx = 0;
    }
    if (BIT_IS_SET(PIND, 1) && (sprites_collision(hero, startplatform) || sprite_collision_any(hero, oddplatforms, 28) || sprite_collision_any(hero, evenplatforms, 28)) && hero.x > 0)
    {
        
        hero.dy = -6;
        hero.y += hero.dy;
        hero.dy = -4;
        hero.y += hero.dy;
        hero.dy = -2;
        hero.y += hero.dy;
    }
    if (((moving == true && BIT_IS_SET(PINB, 1)) || (moving == true && BIT_IS_SET(PIND, 0))) && (sprites_collision(hero, startplatform) || sprite_collision_any(hero, oddplatforms, 28) || sprite_collision_any(hero, evenplatforms, 28)) && hero.x > 0)
    {
        hero.dx = 0;
        moving = false;
    }
    else if (BIT_IS_SET(PINB, 1) && (sprites_collision(hero, startplatform) || sprite_collision_any(hero, oddplatforms, 28) || sprite_collision_any(hero, evenplatforms, 28)) && hero.x > 0)
    {
        hero.dx = -0.5;
        moving = true;
    }
    else if (BIT_IS_SET(PIND, 0) && (sprites_collision(hero, startplatform) || sprite_collision_any(hero, oddplatforms, 28) || sprite_collision_any(hero, evenplatforms, 28)) && hero.x > 0)
    {
        hero.dx = 0.5;
        moving = true;
    }
    hero.x += hero.dx;
    hero.y += hero.dy;
}

void drawAll()
{
    sprite_draw(&hero);
    sprite_draw(&treasure);
    for (int platform = 0; platform < 28; platform++)
    {
        sprite_draw(&oddplatforms[platform]);
        sprite_draw(&evenplatforms[platform]);
    }
    sprite_draw(&startplatform);
}

//FUNCTION THAT SETS UP BUTTONS AND CONTROLS THAT ARE USED
void setup(void)
{
    set_clock_speed(CPU_8MHz);
    lcd_init(LCD_DEFAULT_CONTRAST);
    TCCR1A = 0;
    TCCR1B = 5;
    TIMSK1 = 1;
    sei();
    lives = 10;
    score = 0;
    overflow_count = 0;
    sprite_init(&hero, 40, 2, 3, 3, heroImg);
    sprite_init(&treasure, 2, LCD_Y - 5, 3, 2, treasureImg);
    setup_joystick();

    treasure.dx = 0.3;
    clear_screen();
    while (!gameStart)
    {
        draw_string((LCD_X / 2) - 30, (LCD_Y / 3) - 1, "n10229825", FG_COLOUR);
        draw_string((LCD_X / 2) - 30, ((LCD_Y / 3) * 2) - 1, "Levi Breakwell", FG_COLOUR);

        if (BIT_IS_SET(PINF, 6))
        {
            gameStart = true;
            create_platforms();
        }
        show_screen();
    }
}

ISR(TIMER1_OVF_vect)
{
    overflow_count++;
}

void gamepausescreen()
{
    clear_screen();
    draw_string(10, 10, "Lives: ", FG_COLOUR);
    draw_int(46, 11, lives);
    draw_string(11, 22, "Score: ", FG_COLOUR);
    draw_int(45, 22, score);
    draw_formatted(11, 33, "Time: %02d:%02d", (int)get_elapsed_time() / 60, (int)get_elapsed_time() % 60);
    show_screen();
}

void gameoverscreen()
{
    clear_screen();
    draw_string(20, 10, "GAME OVER!", FG_COLOUR);
    draw_string(11, 22, "Score: ", FG_COLOUR);
    draw_int(45, 22, score);
    draw_formatted(11, 33, "Time: %02d:%02d", (int)get_elapsed_time() / 60, (int)get_elapsed_time() % 60);
    
}

void process(void)
{
    clear_screen();
    while (lives <= 0)
    {
        gameoverscreen();
        show_screen();
        if (BIT_IS_SET(PINF, 5))
        {
            sprite_init(&hero, 40, 2, 3, 3, heroImg);
            sprite_init(&treasure, 2, LCD_Y - 5, 3, 2, treasureImg);
            setup_joystick();
            treasure.dx = 0.3;
            clear_screen();
            create_platforms();
            lives = 10;
            score = 0;
            overflow_count = 0;
            srand(TCNT1);
        }
        if (BIT_IS_SET(PINF, 6))
        {
            clear_screen();
            gameStart = false;
            while (!gameStart)
            {
                draw_string((LCD_X / 2) - 30, (LCD_Y / 3) - 1, "n10229825", FG_COLOUR);
                draw_string((LCD_X / 2) - 30, ((LCD_Y / 3) * 2) - 1, "Levi Breakwell", FG_COLOUR);

                if (BIT_IS_SET(PINF, 6))
                {
                    gameStart = true;
                    create_platforms();
                }
                show_screen();
            }
        }
    }
    if (BIT_IS_SET(PINF, 6))
    {
        clear_screen();
        sprite_init(&hero, 40, 1, 3, 3, heroImg);
        sprite_init(&treasure, 2, LCD_Y - 5, 3, 2, treasureImg);
        setup_joystick();
        treasure.dx = 0.3;
        create_platforms();
        lives = 10;
        score = 0;
        overflow_count = 0;
        srand(TCNT1);
    }
    if (BIT_IS_SET(PINB, 0) && gamepaused == false)
    {
        gamepaused = true;
        gamepausescreen();
    }
    else if (BIT_IS_SET(PINB, 0) && gamepaused == true)
    {
        gamepaused = false;
    }
    if (!gamepaused)
    {
        //platfomrs trying to move
        
        for (int i = 0; i < evencounter ; i++)
        {
            evenplatforms[i].x -= evenplatforms[i].dx;
        }
        for (int i = 0; i < oddcounter ; i++)
        {
            oddplatforms[i].x += oddplatforms[i].dx;

        }
        

        if (sprites_collision(hero, startplatform))
        {
            hero.dy = 0;
        }
        else if (sprite_collision_any(hero, oddplatforms, 28))
        {
            hero.dy = 0;
            for (int plat = 0; plat < 28; plat++)
            {
                if (sprites_collision(hero, oddplatforms[plat]) && oddsafe[plat] == false)
                {
                    lives--;
                    hero.dx = 0;
                    hero.x = 40;
                    hero.y = 2;
                }
                if (sprites_collision(hero, oddplatforms[plat]) && oddsafe[plat] == true)
                {
                    if ((sprites_collision(hero, oddplatforms[plat]) && oddsafe[plat] == true) && alreadyhit == false){
                        score ++ ;
                        alreadyhit = true;
                    }
                    hero.dy = 0;
                    //hero.dx = 0;
                }
            }
        }
        else if (sprite_collision_any(hero, evenplatforms, 28))
        {
            hero.dy = 0;
            for (int plat = 0; plat < 28; plat++)
            {
                if (sprites_collision(hero, evenplatforms[plat]) && evensafe[plat] == false)
                {
                    lives--;
                    hero.dx = 0;
                    hero.x = 40;
                    hero.y = 2;
                }
                if (sprites_collision(hero, evenplatforms[plat]) && evensafe[plat] == true)
                {
                    if (sprites_collision(hero, evenplatforms[plat]) && evensafe[plat] == true && alreadyhit == false){
                        score ++;
                        alreadyhit = true;
                    }
                    
                    hero.dy = 0;
                    
                }
            }
        }
        else
        {
            hero.dy = 0.5;
            alreadyhit = false;
        }
        if (sprites_collision(hero, treasure))
        {
            lives = lives + 2;
            hero.x = 40;
            hero.dx = 0;
            hero.y = 1;
            hero.dy = 0;
            treasure.y = 100;
        }
        if (hero.x <= -3)
        {
            lives--;
            hero.x = 40;
            hero.y = 1;
            hero.dx = 0;
        }

        playermovement();
        treasuremovement();

        drawAll();
        show_screen();
    }
}

int main(void)
{
    setup();
    while (1)
    {
        process();
    }
    return 0;
}