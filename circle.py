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
            theta = (360.0/32.0)*(_id - 1);
            thetar = math.radians(theta)
            x = xoff - 45.0 * math.sin(thetar)
            y = yoff - 45.0 * math.cos(thetar)
            m.SetPosition(pcbnew.wxPointMM(x, y))
            m.SetOrientation((theta+90.0)*10.0)
        m = m.Next()

    pcbnew.Refresh()

def id_to_pos(_id, r):
    
    return (x+xoff, yoff-y, theta);
