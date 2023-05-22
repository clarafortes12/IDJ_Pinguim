#include "Camera.h"
#include "Game.h"
#include "InputManager.h"

GameObject* Camera::focus;
Vec2 Camera::pos;
Vec2 Camera::speed = Vec2(400, 400);

void Camera::Follow(GameObject* newFocus){
    focus = newFocus;
}

void Camera::Unfollow(){
    focus = nullptr;
}

void Camera::Update(float dt){
    if (focus != nullptr) {
        pos = focus->box.GetCentered() - Vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
        return;
    }

    InputManager& intance = InputManager::GetInstance();
    Vec2 newSpeed = speed * dt;

    if (intance.IsKeyDown(LEFT_ARROW_KEY)) {
        pos.x -= newSpeed.x;
    } else if (intance.IsKeyDown(RIGHT_ARROW_KEY)) {
        pos.x += newSpeed.x;
    } else if (intance.IsKeyDown(UP_ARROW_KEY)) {
        pos.y -= newSpeed.y;
    } else if (intance.IsKeyDown(DOWN_ARROW_KEY)) {
        pos.y += newSpeed.y;
    }
}