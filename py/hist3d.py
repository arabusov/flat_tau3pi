#!/usr/bin/python
from ROOT import TH3D
import sys

data=[]
fl=open (sys.argv[1])
h=TH3D  ("hist", "Histogram",100,0.,3.,100,0,3., 100,0,3.)
for line in fl:
  h.Fill (
  float(line.split()[int(sys.argv[2])]),
  float(line.split()[int(sys.argv[3])]),
  float(line.split()[int(sys.argv[4])]))
h.Draw()
raw_input()
