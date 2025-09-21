#ifndef __CONTROL_H
#define __CONTROL_H
 
#include <stdint.h> // 添加此行以定义 int16_t

// 定义麦克纳姆轮小车的移动方向
typedef enum {
    MOVE_FORWARD,
    MOVE_BACKWARD,
    MOVE_TRANSLATE_LEFT,
    MOVE_TRANSLATE_RIGHT,
    MOVE_FORWARD_LEFT,
    MOVE_FORWARD_RIGHT,
    MOVE_BACKWARD_LEFT,
    MOVE_BACKWARD_RIGHT
} MecanumMovementType;


// 麦克纳姆轮小车按指定方向行驶固定距离
void Move_Distance_Mecanum(float distance_cm, int16_t speed, MecanumMovementType movement_type);
void Rotate_Angle(float angle_deg, int16_t speed);
#endif
