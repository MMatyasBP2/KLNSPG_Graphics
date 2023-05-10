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

        if (app.house_state == HOUSE_MOVING_UP && app.scene.secondhousey < -0.09f)
            app.scene.secondhousey += 0.1f;
        else if (app.house_state == HOUSE_MOVING_UP)
            app.house_state = HOUSE_STATIONARY;
    

        if (app.house_state == HOUSE_MOVING_DOWN && app.scene.secondhousey > -17.0f)
            app.scene.secondhousey -= 0.1f;
        else if (app.house_state == HOUSE_MOVING_DOWN)
            app.house_state = HOUSE_STATIONARY;

        update_app(&app);
        render_app(&app);
    }
    destroy_app(&app);

    return 0;
}