import math

# return (x, y, z, w)
def Euler_toQuaternion(roll, pitch, yaw):
    cy = math.cos(yaw * 0.5)
    sy = math.sin(yaw * 0.5)
    cr = math.cos(roll * 0.5)
    sr = math.sin(roll * 0.5)
    cp = math.cos(pitch * 0.5)
    sp = math.sin(pitch * 0.5)
    w = cy * cr * cp + sy * sr * sp
    x = cy * sr * cp - sy * cr * sp
    y = cy * cr * sp + sy * sr * cp
    z = sy * cr * cp - cy * sr * sp
    return (x, y, z, w)

# return Eulerian Angles in
#  !Degrees!
def Quaternion_toEulerianAngle(xyzw):
    x = xyzw[0]
    y = xyzw[1]
    z = xyzw[2]
    w = xyzw[3]

    ysqr = y*y

    t0 = +2.0 * (w * x + y*z)
    t1 = +1.0 - 2.0 * (x*x + ysqr)
    X = math.degrees(math.atan2(t0, t1))

    t2 = +2.0 * (w*y - z*x)
    t2 =  1 if t2 > 1 else t2
    t2 = -1 if t2 < -1 else t2
    Y = math.degrees(math.asin(t2))

    t3 = +2.0 * (w * z + x*y)
    t4 = +1.0 - 2.0 * (ysqr + z*z)
    Z = math.degrees(math.atan2(t3, t4))

    return (X, Y, Z)

# map x in range in_min - in_max to the new range out_min - out_max 
def valueMap(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

# returns rotated x, y
def rotate2D(x, y, alpha):
    # rotation matrix
    tempSin = math.sin(alpha)
    tempCos = math.cos(alpha)
    r11 = tempCos
    r12 = -tempSin
    r21 = tempSin
    r22 = tempCos
    return (r11*x + r12*y, r21*x + r22*y)