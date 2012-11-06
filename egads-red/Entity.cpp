#include "Entity.h"

#include "Rect.h"

Entity::Entity(Vector2f pos, Vector2f extents) : position(pos), extents(extents), type("Entity"), collidable(false), deleteMe(false), next(0), previous(0) {

}

Rect Entity::rect() {
    return Rect(position, extents);
}
