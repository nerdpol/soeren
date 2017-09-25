#!/usr/bin/python

# ZetCode PyGTK tutorial
#
# This code example draws a circle
# using the cairo library
#
# author: jan bodnar
# website: zetcode.com
# last edited: February 2009


import gtk
import math
import gobject

class PyApp(gtk.Window):



    def __init__(self):
        super(PyApp, self).__init__()

        self.x = 1

        self.set_title("Ground Station HUD")
        self.resize(430, 150)
        self.set_position(gtk.WIN_POS_CENTER)

        self.connect("destroy", gtk.main_quit)

        darea = gtk.DrawingArea()
        darea.connect("expose-event", self.expose)
        self.add(darea)

        self.show_all()

        self.w = self.allocation.width
        self.h = self.allocation.height

        # fire up timer (60fps)
        self.timer_next()


    def expose(self, widget, event):
        self.x+=1

        # resize
        self.w = self.allocation.width
        self.h = self.allocation.height

        print "render"
        cr = widget.window.cairo_create()

        cr.set_line_width(9)
        cr.set_source_rgb(0.7, 0.2, 0.0)

        cr.translate(self.w/3, self.h/3)
        cr.arc(0, 0, self.x % 50, 0, 2*math.pi)
        cr.stroke_preserve()

        cr.set_source_rgb(0.3, 0.4, 0.6)
        cr.fill()
        self.draw_artificial_horizon((1, 0, 0, 0), cr)

    def timer_next(self):
        self.queue_draw()
        gobject.timeout_add(16, self.timer_next)

    # q: quaternion (x, y, z, w)
    def draw_artificial_horizon(self, q, cr):
        xyz = self.Quaternion_toEulerianAngle(q[0], q[1], q[2], q[3])
        cr.set_line_width(5)
        cr.set_source_rgb(0.7, 0.2, 0.0)
        cr.translate(self.w/4, self.h/4)
        cr.arc(0, 0, 40, 0, 2*math.pi)
        cr.stroke_preserve()
        cr.fill()
        print xyz

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
