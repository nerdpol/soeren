#!/usr/bin/python3


# Python3
# GTK2 (rewrite to GTK3 possible)
# see wiki for dependencies


import gi
gi.require_version('Gtk', '2.0')
from gi.repository import Gtk as gtk
from gi.repository import GObject as gobject
import cairo
import math


FRAMERATE = 30


class PyApp(gtk.Window):



    def __init__(self):
        super(PyApp, self).__init__()

        # runner variables
        self.qe1 = 1
        self.qe2 = 2.2
        self.qe3 = 3
        self.x = 1

        self.set_title("Ground Station HUD")
        self.resize(430, 150)
        #self.set_position(gtk.WIN_POS_CENTER)

        self.connect("destroy", gtk.main_quit)

        darea = gtk.DrawingArea()

        # gtk3
        #darea.connect("draw", self.render)
        # gtk2
        darea.connect("expose-event", self.render)

        self.add(darea)

        self.show_all()

        # gtk3
        #self.w = self.get_allocation().width
        #self.h = self.get_allocation().height
        # gtk2
        self.w = self.allocation.width
        self.h = self.allocation.height

        # store example quaternions
        # format xyzw
        self.exampleQuats = [
                # facing the sky, slightly rotated to the left
                [-0.346, 0.035, 0.094, 0.933],
                # ?
                [0.373, -0.106, 0.195, 0.901],
                # upside down
                [0, 0, 0.989, 0.142],
                # ?
                [-0.346, 0.035, 0.094, 0.933],
                # earth should be barely visible
                [-0.145, -0.315, 0.393, 0.852]
        ]
        self.numExampleQuats = len(self.exampleQuats)

        # fire up timer
        self.timer_next()

    def timer_next(self):
        self.queue_draw()
        gobject.timeout_add(1000/FRAMERATE, self.timer_next)

    # split visible frame into 4 rectangles
    def drawOutlines(self, cr):
        cr.set_line_width(3)
        cr.set_source_rgb(0.5, 0.5, 0.5)
        cr.rectangle(0, 0, self.w/2, self.h/2)
        cr.stroke_preserve()
        cr.rectangle(self.w/2, 0, self.w/2, self.h/2)
        cr.stroke_preserve()
        cr.rectangle(0, self.h/2, self.w/2, self.h/2)
        cr.stroke_preserve()
        cr.rectangle(self.w/2, self.h/2, self.w/2, self.h/2)
        cr.stroke_preserve()

    def drawExampleCircle(self, cr):
        cr.set_line_width(9)
        cr.set_source_rgb(0.7, 0.2, 0.0)
        cr.translate(3*self.w/4, self.h/4)
        cr.arc(0, 0, self.x % 50, 0, 2*math.pi)
        cr.stroke_preserve()
        cr.set_source_rgb(0.3, 0.4, 0.6)
        cr.fill()


    def render(self, widget, event):
        self.x+=1


        # save (for resizing)
        # gtk3
        #self.w = self.get_allocation().width
        #self.h = self.get_allocation().height
        # gtk2
        self.w = self.allocation.width
        self.h = self.allocation.height

        print("render")

        # drawing context
        cr = widget.window.cairo_create()

        # draw example circle
        cr.save()
        self.drawExampleCircle(cr)
        cr.restore()

        cr.save()
        #self.draw_artificial_horizon((1, 0, 0, 0), cr)
        #self.draw_artificial_horizon(self.exampleQuats[self.x%self.numExampleQuats], cr)
        self.draw_artificial_horizon(self.getNextSampleQuaternion(), cr)
        cr.restore()

        cr.save()
        self.drawOutlines(cr)
        cr.restore()


    # q: quaternion (x, y, z, w)
    def draw_artificial_horizon(self, q, cr):

        xyz = self.Quaternion_toEulerianAngle(q)
        x_deg = xyz[0]
        y_deg = xyz[1]
        z_deg = xyz[2]
        roll = math.radians(x_deg)
        pitch = math.radians(y_deg)
        yaw = math.radians(z_deg)

        # x - roll
        # y - pitch
        # z - yaw
        # really?

        print("Quaternion:      ", q)
        print("Euler (°):       ", xyz)
        print("Euler RPY (Rad): ", (roll, pitch, yaw))
        print("")

        mWidth = self.w/2
        mHeight = self.h/2
        radius = min(mHeight/math.e, mWidth/math.e)

        # calculate angles for drawing the earth
        # this has to be flipped? or changed?
        # seems like earth is always on the wrong side...
        earthStartAngle = roll
        earthEndAngle = roll + math.pi

        # calculate point M (middle of route PQ)
        # check, if we are upside down:
        # upsideDown stuff is kind of wonky...
        # valueMap is not really fixed?
        isUpsideDown = False
        w = self.valueMap(pitch, -math.pi, math.pi, -2*radius, 2*radius)
        if pitch >= math.pi/2 and pitch <= 3*(math.pi/2):
            print("Upside down!")
            w = -w
            isUpsideDown = True

        xc = mWidth/2
        yc = mHeight/2
        beta = (math.pi/2) - earthEndAngle

        # comment in if indicator should relativ the the point
        # between P and Q on the circle
        mx = xc# + (math.cos(beta) * w)
        my = yc - (math.sin(beta) * w)

        # outer, static, circles
        cr.set_source_rgb(0.2, 0.6, 0.85)
        cr.arc(xc, yc, radius+radius*0.2, 0, 2*math.pi)
        cr.fill()
        cr.set_source_rgb(0.627, 0.321, 0.176)
        cr.arc(xc, yc, radius+radius*0.2, 0, -math.pi)
        cr.fill()
        # white gap
        cr.set_source_rgb(1, 1, 1)
        cr.arc(xc, yc, radius+radius*0.05, 0, 2*math.pi)
        cr.fill()

        # sky
        cr.set_line_width(3)
        cr.set_source_rgb(0.7, 0.2, 0.0)
        cr.translate(0, 0)
        cr.arc(mWidth/2, mHeight/2, radius, 0, 2*math.pi)
        cr.clip_preserve()
        cr.stroke_preserve()
        cr.set_source_rgb(0.2, 0.6, 0.85)
        cr.fill()


        # inner circle (earth, brown)
        cr.set_source_rgb(0.627, 0.321, 0.176)
        cr.arc(mx, my, radius*3, earthStartAngle, earthEndAngle)
        cr.fill()


        # white lines
        self.drawAttitudeIndicator(radius=radius, alpha=earthEndAngle, mx=mx, my=my, cr=cr)


        # fixed cross indicator (stays at the same position)
        fixedRadius = radius/6
        cr.set_source_rgb(0, 0, 0)
        cr.arc(mWidth/2, mHeight/2, fixedRadius, 0, math.pi)
        cr.stroke()
        cr.move_to((mWidth/2) - 2*radius/3, mHeight/2)
        cr.line_to((mWidth/2) - fixedRadius, mHeight/2)
        cr.stroke()
        cr.move_to((mWidth/2) + 2*radius/3, mHeight/2)
        cr.line_to((mWidth/2) + fixedRadius, mHeight/2)
        cr.stroke()
        cr.move_to(mWidth/2, mHeight/2)
        cr.line_to(mWidth/2, mHeight/2 + fixedRadius)
        cr.stroke()
        cr.set_line_width(2)
        cr.move_to(mWidth/2, mHeight/2)
        cr.line_to(mWidth/2, mHeight/2 + radius)
        cr.stroke()


        # draw the triangle MC?
        # for geometric debug
        """
        cr.set_source_rgb(0, 0, 0)
        cr.set_line_width(5)
        cr.move_to(xc, yc)
        cr.line_to(mx, my)
        cr.stroke_preserve()
        cr.line_to(mx, yc)
        cr.line_to(xc, yc)
        cr.fill()
        """

        cr.reset_clip()


    def drawAttitudeIndicator(self, radius, alpha, mx, my, cr):

        # white attitude indicator
        # change those params:
        indicators = 5
        indicatorGap = radius/16 #px
        indicatorMaxLen = radius/6
        indicatorLineWidth = radius/32 #px

        cr.set_source_rgb(0.8, 0.8, 0.8)
        cr.set_line_width(indicatorLineWidth)

        cr.save()
        cr.translate(mx, my)
        n = 0
        m = 1
        o = 1
        for i in range(indicators):
            p1x = -indicatorMaxLen/4 if n%2 == 0 else (o)*(-indicatorMaxLen/4)
            p1y = m*indicatorGap
            p2x =  indicatorMaxLen/4 if n%2 == 0 else (o)*( indicatorMaxLen/4)
            p2y = m*indicatorGap
            pAx, pAy = self.rotate2D(p1x, p1y, alpha)
            pBx, pBy = self.rotate2D(p2x, p2y, alpha)
            pCx, pCy = self.rotate2D(pAx, pAy, math.pi)
            pDx, pDy = self.rotate2D(pBx, pBy, math.pi)
            # draw
            cr.move_to(pAx, pAy)
            cr.line_to(pBx, pBy)
            cr.stroke()
            cr.move_to(pCx, pCy)
            cr.line_to(pDx, pDy)
            cr.stroke()
            n += 1
            m += 1
            o += 2

        cr.restore()

        return



    # return Eulerian Angles in
    #  !Degrees!
    def Quaternion_toEulerianAngle(self, xyzw):
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


    # return (x, y, z, w)
    def Euler_toQuaternion(self, roll, pitch, yaw):
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



    def valueMap(self, x, in_min, in_max, out_min, out_max):
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min


    # returns rotated x, y
    def rotate2D(self, x, y, alpha):
        # rotation matrix
        tempSin = math.sin(alpha)
        tempCos = math.cos(alpha)
        r11 = tempCos
        r12 = -tempSin
        r21 = tempSin
        r22 = tempCos
        return (r11*x + r12*y, r21*x + r22*y)

    # returns a tuple (x, y, z, w)
    def getNextSampleQuaternion(self):
        self.qe1 += 0.05
        self.qe2 += 0.03
        self.qe3 += 0.07
        #return self.Euler_toQuaternion(math.sin(self.qe1)*math.pi, math.cos(self.qe2)*math.pi, math.sin(self.qe3))
        roll = -math.sin(self.qe1)*(math.pi/2)
        pitch = math.sin(self.qe2)*(math.pi/2)
        yaw = math.sin(self.qe3)


        print("Input getNext... ", roll, pitch, yaw)
        return self.Euler_toQuaternion(roll, pitch, yaw)

app = PyApp()
gtk.main()
