// 
// Created by Balajanovski on 14/12/2017.
//

#include "Scene.h"
#include "ConfigManager.h"
#include "Constants.h"

void Scene::sceneSDF(IN const Vec3f& position, OUT Intersection& output_intersection) {

    if (ConfigManager::instance().get_amount_of_objects() > 0) {
        auto object = ConfigManager::instance().get_object(0);

        // Use constructive solid geometry to union all the sdfs of the objects
        auto& config_manager_instance = ConfigManager::instance();

        Intersection minimum_intersection;
        config_manager_instance.get_object(0)->sdf(position, minimum_intersection);
        for (int i = 1; i < config_manager_instance.get_amount_of_objects(); ++i) {

            Intersection other_intersection;
            config_manager_instance.get_object(i)->sdf(position, other_intersection);

            minimum_intersection = min(minimum_intersection, other_intersection);
        }

        output_intersection = minimum_intersection;
        return;
    }

    output_intersection = Intersection(Constants::MAX_RENDER_DISTANCE, Constants::BACKGROUND_MATERIAL, position);
    return;

}