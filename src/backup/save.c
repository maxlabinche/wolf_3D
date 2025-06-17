/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** main
*/

#include "palwish.h"

void backup_objects(game_t *game)
{
    FILE *file = fopen("backup.pal", "w");
    object_t *obj;

    if (!file) {
        perror("Erreur lors de l'ouverture du fichier de sauvegarde");
        return;
    }
    for (int i = 0; i < game->object_count; i++) {
        obj = &game->objects[i];
        if (obj->type != 0) {
            fprintf(file,
                "User: %d, Type: %d, X: %.2f, Y: %.2f, Health: %.2f\n",
                obj->user, obj->type, obj->x, obj->y, obj->health);
        }
    }
    fclose(file);
    printf("Sauvegarde terminée dans le fichier\n");
}

void load_backup(game_t *game)
{
    FILE *file = fopen("backup.pal", "r");
    char *line = NULL;
    size_t len = 0;
    network_user_t netu;

    if (!file) {
        return;
    }
    while (getline(&line, &len, file) != -1) {
        if (sscanf(line, "User: %d, Type: %d, X: %lf, Y: %lf, Health: %lf",
            &netu.user, &netu.type, &netu.x, &netu.y, &netu.life) == 5) {
            create_object(game, &netu, false, 1);
        }
    }
    free(line);
    fclose(file);
    printf("Chargement de la sauvegarde terminé depuis le fichier\n");
}
