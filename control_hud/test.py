#!/usr/bin/python3


# Python3
# GTK2 (rewrite to GTK3 possible)
# see wiki for dependencies


import gi
gi.require_version('Gtk', '2.0')
from gi.repository import Gtk as gtk
from gi.repository import GObject as gobject
import math


FRAMERATE = 15


class PyApp(gtk.Window):



    def __init__(self):
        super(PyApp, self).__init__()

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
        cr.translate(self.w/3, self.h/3)
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
        self.drawExampleCircle(cr);
        cr.restore()

        cr.save()
        self.draw_artificial_horizon((1, 0, 0, 0), cr)
        cr.restore()

        cr.save()
        self.drawOutlines(cr)
        cr.restore()


    # q: quaternion (x, y, z, w)
    def draw_artificial_horizon(self, q, cr):

        xyz = self.Quaternion_toEulerianAngle(q[0], q[1], q[2], q[3])

        # x - roll
        # y - pitch
        # z - yaw

        # circle equation
        # x^2 + y^2 = r^2
        # idea: mask the sky circle area
        #       and draw the half earth circle anyway
        # -> no need to do this:
        #    just calc the 2 points and the start and end angle

        mWidth = self.w/2
        mHeight = self.h/2
        radius = min(mHeight/3, mWidth/3)

        cr.set_line_width(3)
        cr.set_source_rgb(0.7, 0.2, 0.0)
        cr.translate(0, 0)

        # outer circle (sky)
        cr.arc(mWidth/2, mHeight/2, radius, 0, 2*math.pi)
        cr.stroke_preserve()
        cr.set_source_rgb(0.2, 0.6, 0.85)
        cr.fill()

        # inner circle (earth, green)
        cr.set_source_rgb(0.3, 0.6, 0.1)
        # test
        #cr.arc(mWidth/2, mHeight/2, radius, math.sin((xyz[0]*math.pi/360)), math.sin((math.pi*xyz[0]/360) - math.pi))
        cr.arc(mWidth/2, mHeight/2, radius, math.pi/4, (math.pi/2) + 1)
        cr.fill()

        # inner cross
        #cr.translate((mWidth/4) - radius, mHeight/4)
        cr.set_line_width(4)
        cr.set_source_rgb(0, 0, 0)

        # TODO horizontal line
        # calc the anchor points on the circle
        # -> x - roll
        cr.move_to((mWidth/2) - radius*.7, mHeight/2)
        cr.line_to((mWidth/2) + radius*.7, mHeight/2)
        cr.stroke()

        # TODO vertical line
        # -> y - pitch
        cr.move_to(mWidth/2, (mHeight/2) + radius/2)
        cr.line_to(mWidth/2, (mHeight/2) - radius/2)
        cr.stroke()
        #cr.fill()

        print(xyz)

    def Quaternion_toEulerianAngle(self, x, y, z, w):
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


app = PyApp()
gtk.main()
