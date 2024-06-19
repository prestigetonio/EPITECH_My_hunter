/*
** EPITECH PROJECT, 2023
** header Myhunter
** File description:
** hunter project 2
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/hunter.h"

void drawCurrentBirdPhase(sfRenderWindow *window, int current_phase, sfSprite *phase1, sfSprite *phase2, sfSprite *phase3, Hitbox *oiseau_hitbox)
{
    switch (current_phase) {
        case 1:
            sfSprite_setPosition(phase1, (sfVector2f){oiseau_hitbox->x, oiseau_hitbox->y});
            sfRenderWindow_drawSprite(window, phase1, NULL);
            break;
        case 2:
            sfSprite_setPosition(phase2, (sfVector2f){oiseau_hitbox->x, oiseau_hitbox->y});
            sfRenderWindow_drawSprite(window, phase2, NULL);
            break;
        case 3:
            sfSprite_setPosition(phase3, (sfVector2f){oiseau_hitbox->x, oiseau_hitbox->y});
            sfRenderWindow_drawSprite(window, phase3, NULL);
            break;
    }
}

void initSounds(sfSound **clickSound, sfSound **clickSound_kill)
{
    sfSoundBuffer *buffer = sfSoundBuffer_createFromFile("sound/raygun.ogg");
    *clickSound = sfSound_create();
    sfSound_setVolume(*clickSound, 15);
    sfSound_setBuffer(*clickSound, buffer);
    sfSoundBuffer *buffer2 = sfSoundBuffer_createFromFile("sound/kill.ogg");
    *clickSound_kill = sfSound_create();
    sfSound_setVolume(*clickSound_kill, 15);
    sfSound_setBuffer(*clickSound_kill, buffer2);
}

void updateBirdPhase(sfSprite *phase1, sfSprite *phase2, sfSprite *phase3, sfTexture *texture1, sfTexture *texture2, sfTexture *texture3, int *current_phase, sfClock *clock, sfBool *spawnNewBird, Hitbox *oiseau_hitbox, sfVideoMode video)
{
    sfTime elapsedTime = sfClock_getElapsedTime(clock);
    sfTime phase_during = sfMilliseconds(500);
    if (sfTime_asMilliseconds(elapsedTime) >= sfTime_asMilliseconds(phase_during)) {
        sfClock_restart(clock);
        switch (*current_phase) {
            case 1:
                sfSprite_setTexture(phase1, texture1, sfTrue);
                break;
            case 2:
                sfSprite_setTexture(phase2, texture2, sfTrue);
                break;
            case 3:
                sfSprite_setTexture(phase3, texture3, sfTrue);
                break;
        }
        *current_phase = (*current_phase % 3) + 1;
        if (*spawnNewBird) {
            oiseau_hitbox->x = 0.0f;
            oiseau_hitbox->y = rand() % (video.height - (int)oiseau_hitbox->height);
            *spawnNewBird = sfFalse;
        }
    }
}

void Allscales(sfSprite *sprite, sfSprite *phase1, sfSprite *phase2, sfSprite *phase3, sfSprite *snipe)
{
    sfVector2f scale = {1.12, 1.12};
    sfVector2f scale_bird = {2.0, 2.0};
    sfVector2f scale_snipe = {0.2, 0.2};
    sfSprite_setScale(sprite, scale);
    sfSprite_setScale(phase1, scale_bird);
    sfSprite_setScale(phase2, scale_bird);
    sfSprite_setScale(phase3, scale_bird);
    sfSprite_setScale(snipe, scale_snipe);
}
