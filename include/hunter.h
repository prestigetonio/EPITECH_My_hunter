/*
** EPITECH PROJECT, 2023
** hunter.h
** File description:
** hunter.h
*/

#ifndef HUNTER_H
#define HUNTER_H

typedef struct {
    float x, y;
    float width, height;
    int isVisible;
} Hitbox;

typedef struct {
    sfMouseButtonEvent event;
    sfSound *clickSound;
    sfSound *clickSound_kill;
} Mouseclick;

typedef struct {
    sfRenderWindow *window;
    sfMusic *music;
    sfSound *clickSound;
    sfSound *clickSound_kill;
    sfSoundBuffer *buffer;
    sfSoundBuffer *buffer2;
    sfTexture *texture;
    sfSprite *sprite;
    sfTexture *texture02;
    sfSprite *snipe;
    sfTexture *texture1;
    sfTexture *texture2;
    sfTexture *texture3;
    sfSprite *phase1;
    sfSprite *phase2;
    sfSprite *phase3;
    sfClock *clock;
    sfClock *spawnClock;
} GameResources;

typedef struct {
    Hitbox *hitbox;
    float vitesse;
    float windowWidth;
    float windowHeight;
} DeplacementParams;

void mettreAJourPhase(sfClock *clock, sfTime elapsedTime, sfTime phase_during, int *current_phase, sfSprite *phase1, sfSprite *phase2, sfSprite *phase3, sfTexture *texture1, sfTexture *texture2, sfTexture *texture3, sfBool *spawnNewBird, Hitbox *oiseau_hitbox, sfVideoMode video);
sfMusic *MakeMusic(void);
void updateBirdPhase(sfSprite *phase1, sfSprite *phase2, sfSprite *phase3, sfTexture *texture1, sfTexture *texture2, sfTexture *texture3, int *current_phase, sfClock *clock, sfBool *spawnNewBird, Hitbox *oiseau_hitbox, sfVideoMode video);
void mettreAJourPhase(sfClock *clock, sfTime elapsedTime, sfTime phase_during, int *current_phase, sfSprite *phase1, sfSprite *phase2, sfSprite *phase3, sfTexture *texture1, sfTexture *texture2, sfTexture *texture3, sfBool *spawnNewBird, Hitbox *oiseau_hitbox, sfVideoMode video);
void Allscales(sfSprite *sprite, sfSprite *phase1, sfSprite *phase2, sfSprite *phase3, sfSprite *snipe);
void loadTexturesAndSprites(sfTexture **texture, sfTexture **texture02, sfTexture **texture1, sfTexture **texture2, sfTexture **texture3, sfSprite **sprite, sfSprite **snipe, sfSprite **phase1, sfSprite **phase2, sfSprite **phase3);
void drawCurrentBirdPhase(sfRenderWindow *window, int current_phase, sfSprite *phase1, sfSprite *phase2, sfSprite *phase3, Hitbox *oiseau_hitbox);
void initSounds(sfSound **clickSound, sfSound **clickSound_kill);
static void destroy_resources(GameResources *resources);
void drawScore(sfRenderWindow *window, sfSprite *snipe, int counter);
static int clique_inside_bird(sfMouseButtonEvent event, Hitbox *oiseau_hitbox);
static void analyse_events(sfRenderWindow *window, sfEvent event, sfSound *clickSound, sfSound *clickSound_kill, Hitbox *oiseau_hitbox, int *counter, sfClock *spawnClock, sfBool *spawnNewBird, sfSprite *phase1, sfSprite *phase2, sfSprite *phase3);
static void manage_mouse_click(Mouseclick args, sfEvent event);
static void deplacerHitbox(Hitbox *hitbox, float vitesse, float windowWidth, float windowHeight);
#endif
