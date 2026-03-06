import time
import math
from media.sensor import *
# 去掉不必要的显示反馈
from machine import FPIOA, PWM, Pin

FRAME_W = 640
FRAME_H = 360

FOV_H = 63.6
FOV_V = 38.0

fov_h_rad = math.radians(FOV_H)
fov_v_rad = math.radians(FOV_V)
F_H = (FRAME_W / 2) / math.tan(fov_h_rad / 2)
F_V = (FRAME_H / 2) / math.tan(fov_v_rad / 2)

REAL_HEIGHT_MM = 100.0

black_tape_threshold = (0, 31, -128, 127, -128, 39)
DENSITY_THRESHOLD = 0.5

VERT_MIN_PULSE = 870
VERT_MAX_PULSE = 2170
VERT_ANGLE_MIN = 0
VERT_ANGLE_MAX = 180

HORIZ_MIN_PULSE = 1100
HORIZ_MAX_PULSE = 2500
HORIZ_ANGLE_MIN = 0
HORIZ_ANGLE_MAX = 180

BASE_H = 90
BASE_V = 90

fpioa = FPIOA()
fpioa.set_function(42, FPIOA.PWM0)
fpioa.set_function(43, FPIOA.PWM1)
fpioa.set_function(35, FPIOA.GPIO35)

done_pin = Pin(35, Pin.OUT, pull=Pin.PULL_NONE, drive=7)
done_pin.value(0)

servo_horiz = PWM(0, 50, 0, enable=True)
servo_vert = PWM(1, 50, 0, enable=True)

def angle_to_pulse(angle, min_angle, max_angle, min_pulse, max_pulse):
    if angle < min_angle:
        angle = min_angle
    elif angle > max_angle:
        angle = max_angle
    ratio = (angle - min_angle) / (max_angle - min_angle)
    pulse = min_pulse + (max_pulse - min_pulse) * ratio
    return int(pulse)

def pulse_to_duty(pulse_us):
    return (pulse_us / 20000.0) * 100.0

def set_horizontal_angle(angle):
    pulse = angle_to_pulse(angle, HORIZ_ANGLE_MIN, HORIZ_ANGLE_MAX, HORIZ_MIN_PULSE, HORIZ_MAX_PULSE)
    duty = pulse_to_duty(pulse)
    duty = max(0.0, min(100.0, duty))
    servo_horiz.duty(duty)

def set_vertical_angle(angle):
    pulse = angle_to_pulse(angle, VERT_ANGLE_MIN, VERT_ANGLE_MAX, VERT_MIN_PULSE, VERT_MAX_PULSE)
    duty = pulse_to_duty(pulse)
    duty = max(0.0, min(100.0, duty))
    servo_vert.duty(duty)

set_horizontal_angle(BASE_H)
set_vertical_angle(BASE_V)

def get_angle_offset(cx, cy):
    center_x = FRAME_W / 2
    center_y = FRAME_H / 2
    dx = cx - center_x
    dy = cy - center_y
    angle_h = math.atan(dx / F_H)
    angle_v = -math.atan(dy / F_V)
    return math.degrees(angle_h), math.degrees(angle_v)

def estimate_distance(blob_height_pixels):
    if blob_height_pixels == 0:
        return None
    return (REAL_HEIGHT_MM * F_V) / blob_height_pixels

def compute_change_h(angle_h, angle_v):
    ah = abs(angle_h)
    if angle_v < 13:
        if angle_h > 0:
            if ah > 25:
                return 11
            elif ah > 20:
                return 9
            elif 15 < ah <= 20:
                return 5
            elif 10 < ah <= 15:
                return 5
            elif ah <= 10:
                return 3
        else:
            if ah > 25:
                return 2
            elif ah > 20:
                return 2
            elif 15 < ah <= 20:
                return 3
            elif 10 < ah <= 15:
                return 3
            elif ah <= 10:
                return 3
    else:
        if angle_h > 0:
            if ah > 25:
                return 13
            elif 20 < ah <= 25:
                return 9
            elif 15 < ah <= 20:
                return 7
            elif 10 < ah <= 15:
                return 5
            elif ah <= 10:
                return 3
        else:
            if ah > 25:
                return 5
            elif ah > 20:
                return 2
            elif 15 < ah <= 20:
                return 5
            elif 10 < ah <= 15:
                return 3
            elif ah <= 10:
                return 3
    return 0

def compute_change_v(distance_mm):
    if distance_mm is None or distance_mm <= 0:
        return 0.0
    elif distance_mm >= 800:
        return 5
    elif distance_mm <= 700:
        return -3
    return 0.0

def move_servo(angle_h, angle_v, blob_height_pixels=None):
    change_h = compute_change_h(angle_h, angle_v)
    distance_mm = estimate_distance(blob_height_pixels) if blob_height_pixels is not None else None
    change_v = compute_change_v(distance_mm)
    target_h = BASE_H - angle_h - change_h
    target_v = BASE_V + angle_v + change_v
    target_h = max(HORIZ_ANGLE_MIN, min(HORIZ_ANGLE_MAX, target_h))
    target_v = max(VERT_ANGLE_MIN, min(VERT_ANGLE_MAX, target_v))
    set_horizontal_angle(target_h)
    set_vertical_angle(target_v)

sensor = Sensor(id=2)
sensor.reset()
sensor.set_framesize(width=FRAME_W, height=FRAME_H)
sensor.set_pixformat(Sensor.RGB565)
try:
    sensor.set_auto_whitebal(False)
    sensor.set_auto_gain(False)
    sensor.set_auto_exposure(False)
except Exception:
    pass

# 保留 MediaManager 初始化以免依赖
MediaManager.init()
sensor.run()

done_pin.value(0)

adjusted = False

while True:
    img = sensor.snapshot()

    if not adjusted:
        blobs = img.find_blobs([black_tape_threshold], area_threshold=200, pixels_threshold=200, merge=True, margin=15)
        if blobs:
            hollow_blobs = [b for b in blobs if b.density() < DENSITY_THRESHOLD]
            if hollow_blobs:
                max_blob = max(hollow_blobs, key=lambda b: b.pixels())
                bx, by = max_blob.cx(), max_blob.cy()
                angle_h, angle_v = get_angle_offset(bx, by)
                move_servo(angle_h, angle_v, max_blob.h())
                time.sleep(0.05)  # 缩短等待
                adjusted = True
                done_pin.value(1)

    time.sleep(0.005)  # 减少主循环延迟
