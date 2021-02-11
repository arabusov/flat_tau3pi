#!/usr/bin/python
from ROOT import TH1D
import sys

data=[]
fl=open (sys.argv[1])
h=TH1D  ("hist", "Histogram",1000,-1,100)
for line in fl:
  h.Fill (float(line.split()[int(sys.argv[2])]))
h.Draw()
raw_input()
