// 
// Created by Balajanovski on 14/12/2017.
//

#include "Scene.h"
#include "ConfigManager.h"
#include "Constants.h"

Intersection&& Scene::sceneSDF(const Vec3f &position) {

    if (ConfigManager::instance().get_amount_of_objects() > 0) {
        auto object = ConfigManager::instance().get_object(0);

        // Use constructive solid geometry to union all the sdfs of the objects
        auto minimum_intersection = ConfigManager::instance().get_object(0)->sdf(position);
        for (int i = 1; i < ConfigManager::instance().get_amount_of_objects(); ++i) {
            auto other_intersection = ConfigManager::instance().get_object(i)->sdf(position);
            minimum_intersection = min(minimum_intersection, other_intersection);
        }

        return std::move(minimum_intersection);
    }

    return Intersection(Constants::MAX_RENDER_DISTANCE, Constants::BACKGROUND_MATERIAL, position);

}