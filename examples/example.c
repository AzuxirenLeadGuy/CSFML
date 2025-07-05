#include <CSFML/Audio.h>
#include <CSFML/Graphics.h>

#include <stdlib.h>

const unsigned char doodle_pop_ogg[] = {
#embed "doodle_pop.ogg"
};

const unsigned char sfml_logo_png[] = {
#embed "sfml_logo.png"
};

const unsigned char tuffy_ttf[] = {
#embed "tuffy.ttf"
};


int main(void)
{
    // Create the main window
    const sfVideoMode mode   = {{800, 600}, 32};
    sfRenderWindow*   window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, sfWindowed, nullptr);
    if (!window)
        return EXIT_FAILURE;

    // Load a sprite to display
    const sfTexture* texture = sfTexture_createFromMemory(sfml_logo_png, sizeof(sfml_logo_png), nullptr);
    if (!texture)
    {
        sfRenderWindow_destroy(window);
        return EXIT_FAILURE;
    }
    sfSprite*        sprite         = sfSprite_create(texture);
    const sfVector2f spritePosition = {200, 200};
    sfSprite_setPosition(sprite, spritePosition);

    // Create a graphical text to display

    const sfFont* font = sfFont_createFromMemory(tuffy_ttf, sizeof(tuffy_ttf));
    if (!font)
    {
        sfSprite_destroy(sprite);
        sfTexture_destroy(texture);
        sfRenderWindow_destroy(window);
        return EXIT_FAILURE;
    }
    sfText* text = sfText_create(font);
    sfText_setString(text, "Hello, SFML!");
    sfText_setCharacterSize(text, 50);

    // Load a music to play
    sfMusic* music = sfMusic_createFromMemory(doodle_pop_ogg, sizeof(doodle_pop_ogg));
    if (!music)
    {
        sfText_destroy(text);
        sfFont_destroy(font);
        sfSprite_destroy(sprite);
        sfTexture_destroy(texture);
        sfRenderWindow_destroy(window);
        return EXIT_FAILURE;
    }

    // Play the music
    sfMusic_play(music);

    // Start the game loop
    sfEvent event;
    while (sfRenderWindow_isOpen(window))
    {
        // Process events
        while (sfRenderWindow_pollEvent(window, &event))
        {
            // Close window : exit
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        // Clear the screen
        sfRenderWindow_clear(window, sfBlack);

        // Draw the sprite
        sfRenderWindow_drawSprite(window, sprite, nullptr);

        // Draw the text
        sfRenderWindow_drawText(window, text, nullptr);

        // Update the window
        sfRenderWindow_display(window);
    }

    // Cleanup resources
    sfMusic_destroy(music);
    sfText_destroy(text);
    sfFont_destroy(font);
    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
    sfRenderWindow_destroy(window);

    return EXIT_SUCCESS;
}
