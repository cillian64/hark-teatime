import math
import pcbnew

xoff = 100.0
yoff = 100.0

def main():
    brd = pcbnew.GetBoard()
    m = brd.GetModules()

    while m is not None:
        print(m.GetReference())
        if m.GetReference()[0] == "D":
            _id = int(m.GetReference()[1:])
            (x, y, rot) = id_to_pos(_id, 45.0)
            m.SetPosition(pcbnew.wxPointMM(x, y))
            m.SetOrientation(-(rot-90.0)*10.0)
        if m.GetReference()[0] == "R":
            _id = int(m.GetReference()[1:])
            if( _id < 9):
                m.SetOrientationDegrees(90)
            if( _id >= 9 and _id < 17):
                m.SetOrientationDegrees(0)
            if( _id >= 17 and _id < 25):
                m.SetOrientationDegrees(-90)
            if( _id >= 25):
                m.SetOrientationDegrees(-180)

        m = m.Next()

    pcbnew.Refresh()

def id_to_pos(_id, r):
    theta = (360.0/32.0)*(_id - 1);
    thetar = math.radians(theta)
    x = r * math.sin(thetar)
    y = r * math.cos(thetar)
    return (x+xoff, yoff-y, theta);
