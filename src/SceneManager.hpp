/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : SceneManager
 * @created     : Wednesday Jan 08, 2025 19:14:50 CET
 */

#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include "ECS.hpp"

#include <GLFW/glfw3.h>

class SceneManager {
public:
    static void setup_scene(Scene &scene);
    static void setup_win_scene(Scene &scene);
    static void setup_menu_scene(Scene &scene);
    static void setup_loose_scene(Scene &scene);
    static void register_and_initialize_systems(float &delta_time);
    static void change_scene(Scene &current_scene, float &delta_time, std::function<void(Scene&)> setup_scene, std::function<void(float&)> register_and_initialize_systems = nullptr);
    static void register_end(float& delta_time); 

    static bool has_restarted;
    static bool is_win;
    static bool is_loose;
    static bool end_scene;
    static bool chose_menu;
    static bool is_select;
};

#endif 

