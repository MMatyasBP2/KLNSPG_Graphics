#include "app.h"

#include <stdio.h>

/**
 * Main function
 */
int main(int argc, char* argv[])
{
    App app;
    
    init_app(&app, 1280, 720);
    while (app.is_running) {
        handle_app_events(&app);

        if (app.housemovingup && app.scene.secondhousey > -20.0f)
            app.scene.secondhousey += 0.1f;

        update_app(&app);
        render_app(&app);
    }
    destroy_app(&app);

    return 0;
}
