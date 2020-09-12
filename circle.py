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
            print("D inner")
            _id = int(m.GetReference()[1:])
            theta = (360.0/32.0)*(_id - 1);
            thetar = math.radians(theta)
            x = xoff - 23.5 * math.sin(thetar)
            y = yoff - 23.5 * math.cos(thetar)
            m.SetPosition(pcbnew.wxPointMM(x, y))
            m.SetOrientation((theta+90.0)*10.0)
        if m.GetReference()[0] == "R":
            print("R inner")
            _id = int(m.GetReference()[1:])
            theta = (360.0/32.0)*(_id - 1);
            thetar = math.radians(theta)
            x = xoff - 21 * math.sin(thetar)
            y = yoff - 21 * math.cos(thetar)
            m.SetPosition(pcbnew.wxPointMM(x, y))
            m.SetOrientation((theta+180)*10.0)
        m = m.Next()

    pcbnew.Refresh()

def id_to_pos(_id, r):
    
    return (x+xoff, yoff-y, theta);
