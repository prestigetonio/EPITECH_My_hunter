/*
** EPITECH PROJECT, 2023
** header Myhunter
** File description:
** hunter project
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/hunter.h"

int main(void)
{
    sfVideoMode video = {1920, 1080, 32};
    sfRenderWindow *window;
    sfEvent event;
    GameResources fullresources;
    sfTexture *texture, *texture02, *texture1, *texture2, *texture3;
    sfSprite *sprite, *snipe, *phase1, *phase2, *phase3;
    loadTexturesAndSprites(&texture, &texture02, &texture1, &texture2, &texture3, &sprite, &snipe, &phase1, &phase2, &phase3);
    Allscales(sprite, phase1, phase2, phase3, snipe);
    window = sfRenderWindow_create(video, "HUNTER", sfResize | sfClose, NULL);
    sfSound *clickSound;
    sfSound *clickSound_kill;
    initSounds(&clickSound, &clickSound_kill);
    sfMusic *music = MakeMusic();
    sfClock *clock = sfClock_create();
    sfClock *spawnClock = sfClock_create();
    sfTime elapsedTime;
    sfTime phase_during = sfMilliseconds(500);
    sfBool spawnNewBird = sfTrue;
    int current_phase = 1;
    int counter = 0;
    Hitbox oiseau_hitbox;
    oiseau_hitbox.x = 0.0f;
    oiseau_hitbox.y = 0.0f;
    oiseau_hitbox.width = sfSprite_getGlobalBounds(phase1).width;
    oiseau_hitbox.height = sfSprite_getGlobalBounds(phase1).height;
    float vitesseDeplacementOiseau = 0.5f;
    srand(time(NULL));
    while (sfRenderWindow_isOpen(window)) {
        drawScore(window, snipe, counter);
        while (sfRenderWindow_pollEvent(window, &event)) {
            analyse_events(window, event, clickSound, clickSound_kill, &oiseau_hitbox, &counter, spawnClock, &spawnNewBird, phase1, phase2, phase3);
        }
        sfRenderWindow_setMouseCursorVisible(window, sfFalse);
        sfVector2i mouse_position = sfMouse_getPositionRenderWindow(window);
        sfVector2f snipe_position = {
            mouse_position.x - sfSprite_getGlobalBounds(snipe).width / 2,
            mouse_position.y - sfSprite_getGlobalBounds(snipe).height / 2
        };
        sfSprite_setPosition(snipe, snipe_position);
        elapsedTime = sfClock_getElapsedTime(clock);
        updateBirdPhase(phase1, phase2, phase3, texture1, texture2, texture3, &current_phase, clock, &spawnNewBird, &oiseau_hitbox, video);
        sfRenderWindow_clear(window, sfBlack);
        sfVector2f windowSize = {(float)video.width, (float)video.height};
        sfVector2f scale = {windowSize.x / sfTexture_getSize(texture).x, windowSize.y / sfTexture_getSize(texture).y};
        sfSprite_setScale(sprite, scale);
        sfRenderWindow_drawSprite(window, sprite, NULL);
        deplacerHitbox(&oiseau_hitbox, vitesseDeplacementOiseau, (float)video.width, (float)video.height);
        switch (current_phase) {
            case 1:
            case 2:
            case 3:
                drawCurrentBirdPhase(window, current_phase, phase1, phase2, phase3, &oiseau_hitbox);
                break;
        }
    }
    destroy_resources(&fullresources);
    return 0;
}

void loadTexturesAndSprites(sfTexture **texture, sfTexture **texture02, sfTexture **texture1, sfTexture **texture2, sfTexture **texture3, sfSprite **sprite, sfSprite **snipe, sfSprite **phase1, sfSprite **phase2, sfSprite **phase3)
{
    *texture = sfTexture_createFromFile("img/background.jpg", NULL);
    *texture02 = sfTexture_createFromFile("img/snipe.png", NULL);
    *texture1 = sfTexture_createFromFile("img/piaf_ph1.png", NULL);
    *texture2 = sfTexture_createFromFile("img/piaf_ph2.png", NULL);
    *texture3 = sfTexture_createFromFile("img/piaf_ph3.png", NULL);
    *sprite = sfSprite_create();
    *snipe = sfSprite_create();
    *phase1 = sfSprite_create();
    *phase2 = sfSprite_create();
    *phase3 = sfSprite_create();
    sfSprite_setTexture(*sprite, *texture, sfTrue);
    sfSprite_setTexture(*phase1, *texture1, sfTrue);
    sfSprite_setTexture(*phase2, *texture2, sfTrue);
    sfSprite_setTexture(*phase3, *texture3, sfTrue);
    sfSprite_setTexture(*snipe, *texture02, sfTrue);
}

void int_to_str(int counter, char *counter_text)
{
    int temp = counter;
    int length = 0;
    if (temp == 0) {
        counter_text[0] = '0';
        counter_text[1] = '\0';
        length = 1;
    } else {
        while (temp > 0) {
            temp /= 10;
            length++;
        }
        counter_text[length] = '\0';
        for (int i = length - 1; i >= 0; i--) {
            counter_text[i] = '0' + counter % 10;
            counter /= 10;
        }
    }
}

void drawScore(sfRenderWindow *window, sfSprite *snipe, int counter)
{
    sfRenderWindow_drawSprite(window, snipe, NULL);
    sfFont *font = sfFont_createFromFile("font.ttf");
    sfText *text = sfText_create();
    char *counter_text = malloc(sizeof(char) * 20);
    int_to_str(counter, counter_text);
    sfText_setString(text, counter_text);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 70);
    sfText_setPosition(text, (sfVector2f){1500.0f, 1000.0f});
    sfText_setColor(text, sfBlack);
    sfRenderWindow_drawText(window, text, NULL);
    sfRenderWindow_display(window);
}

static void destroy_resources(GameResources *resources)
{
    sfMusic_destroy(resources->music);
    sfSound_destroy(resources->clickSound);
    sfSound_destroy(resources->clickSound_kill);
    sfSoundBuffer_destroy(resources->buffer);
    sfSoundBuffer_destroy(resources->buffer2);
    sfTexture_destroy(resources->texture);
    sfSprite_destroy(resources->sprite);
    sfTexture_destroy(resources->texture02);
    sfSprite_destroy(resources->snipe);
    sfTexture_destroy(resources->texture1);
    sfTexture_destroy(resources->texture2);
    sfTexture_destroy(resources->texture3);
    sfSprite_destroy(resources->phase1);
    sfSprite_destroy(resources->phase2);
    sfSprite_destroy(resources->phase3);
    sfClock_destroy(resources->clock);
    sfClock_destroy(resources->spawnClock);
    sfRenderWindow_destroy(resources->window);
}

sfMusic *MakeMusic(void)
{
    sfMusic *music = sfMusic_createFromFile("sound/music.ogg");
    sfMusic_play(music);
    sfMusic_setVolume(music, 15);
    return music;
}

static void deplacerHitbox(Hitbox *hitbox, float vitesse, float windowWidth, float windowHeight)
{
    hitbox->x += vitesse;

    if (hitbox->x > windowWidth) {
        hitbox->x = -hitbox->width;
        hitbox->y = rand() % (int)(windowHeight - hitbox->height);
    }
}

static int clique_inside_bird(sfMouseButtonEvent event, Hitbox *oiseau_hitbox)
{
    sfFloatRect birdHitbox = {oiseau_hitbox->x, oiseau_hitbox->y, oiseau_hitbox->width, oiseau_hitbox->height};
    return sfFloatRect_contains(&birdHitbox, event.x, event.y);
}

static void analyse_events(sfRenderWindow *window, sfEvent event, sfSound *clickSound, sfSound *clickSound_kill, Hitbox *oiseau_hitbox, int *counter, sfClock *spawnClock, sfBool *spawnNewBird, sfSprite *phase1, sfSprite *phase2, sfSprite *phase3)
{
    Mouseclick args;
    if (event.type == sfEvtClosed) sfRenderWindow_close(window);
    else if (event.type == sfEvtMouseButtonPressed && event.mouseButton.button == sfMouseLeft) {
        if (clique_inside_bird(event.mouseButton, oiseau_hitbox)) {
            oiseau_hitbox->x = -1000.0f;
            oiseau_hitbox->y = -1000.0f;
            sfSound_play(clickSound_kill);
            (*counter)++;
        } else manage_mouse_click(args, event);
        *spawnNewBird = sfTrue;
        sfClock_restart(spawnClock);
    }
    sfTime spawnTime = sfClock_getElapsedTime(spawnClock);
}

static void manage_mouse_click(Mouseclick args, sfEvent event)
{
    if (event.type == sfEvtMouseButtonPressed) {
        sfSound_play(args.clickSound);
    } else if (event.type == sfEvtMouseButtonPressed) {
        sfSound_play(args.clickSound_kill);
    }
}
