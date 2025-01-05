/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : Systems
 * @created     : Saturday Jan 04, 2025 20:52:04 CET
 */

#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include "Components.hpp"
#include "ECS.hpp"

#include <vector>

class MeshSystem
{
  public:
     MeshSystem() = delete;
    ~MeshSystem();
    
    static void upload(std::vector<Entity> entities, void *args);
    static void draw(std::vector<Entity> entities, void *args);
    static void init(std::vector<Entity> entities, void *args);
    static void end(std::vector<Entity> entities, void *args);

  private:
};


class TextureSystem
{
  public:
    TextureSystem () = delete;
    ~TextureSystem();

    static void init(std::vector<Entity> entities, void *args);
    static void load(std::vector<Entity> entities, void *args);
    static void draw(std::vector<Entity> entities, void *args);

  private:
};


class PhysicSystem
{
  public:
    PhysicSystem() = delete;
    ~PhysicSystem();

    static void update(std::vector<Entity> entities, void *args);

  private:
};


class ControllerSystem
{
  public:
    ControllerSystem() = delete;
    ~ControllerSystem();

    static void process_input(std::vector<Entity> entities, void *args);

  private:
};

#endif 

